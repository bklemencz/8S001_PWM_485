
#include "stm8s.h"
#include "eeprom.h"
#include "EV1527.h"
#include "gamma.h"
#include "settings.h"




uint32_t EV1527_Stored_Codes[4];
uint8_t serialbuff[7];
uint8_t bufflen,Ramp1ms;
bool serialrec,NIGHTMODEEN,MOTIONEN,DutyChanged,Manual_OVR;
uint8_t ID,GroupID,RampTime,MaxDuty,NightDuty,Ch1Save,Ch2Save,Ch3Save;
uint8_t Ch1TGT,Ch2TGT,Ch3TGT;
uint16_t Ch1Duty,Ch2Duty,Ch3Duty,MaxAct;

volatile uint16_t Timer_last_valid_packet_10us;
volatile uint16_t Timer_last_edge_10us;
volatile uint16_t EV1527_Hightime;
volatile uint16_t EV1527_LowTime;
volatile bool EV1527_BitReady,Timer_ms,PIR_On;
uint16_t Timer_ms_to_s;

uint32_t EV1527_Rec_Code;
uint32_t EV1527_Valid_Rec_Code;
uint8_t EV1527_Rec_Data;
uint8_t EV1527_Valid_Rec_Data;
uint8_t EV1527_Repeat_Count;
bool EV1527_Valid_Code;
bool EV1527_Valid_Learn_Code;
bool EV1527_Valid_Data;
bool Motion_Active;
uint8_t RF_Motion_On_Time_10s;
uint16_t Motion_On_Timer;

void _delay_us (uint16_t us)
{
	uint16_t i;
	uint16_t cy;
	cy = T_COUNT(us);
	_asm("nop\n $N:\n decw X\n jrne $L\n nop\n ", cy);
	
}

void _delay_ms( uint16_t ms )
{
	while ( ms-- )
	{
		_delay_us( 1000 );
	}
}

void Motion_Detected(void)
{
	if (MOTIONEN == TRUE)
	{
		Motion_On_Timer = 0;
		Motion_Active = TRUE;
		Ch1TGT = Ch1Save;
		Ch2TGT = Ch2Save;
	}
}

void LoadSettings(void)
{
	
	ID = EEPROM_ReadByte(0);
	GroupID = EEPROM_ReadByte(1);
	RampTime = EEPROM_ReadByte(2);
	MaxDuty = EEPROM_ReadByte(3);
	NightDuty = EEPROM_ReadByte(4);
	Ch1Save = EEPROM_ReadByte(5);
	Ch2Save = EEPROM_ReadByte(6);
	Ch3Save = EEPROM_ReadByte(7);
	RF_Motion_On_Time_10s = EEPROM_ReadByte(8);
	MOTIONEN = EEPROM_ReadByte(9);
	EV1527_Stored_Codes[0] = EEPROM_Read4Byte(10);
	EV1527_Stored_Codes[1] = EEPROM_Read4Byte(14);
	EV1527_Stored_Codes[2] = EEPROM_Read4Byte(18);
	EV1527_Stored_Codes[3] = EEPROM_Read4Byte(22);
	MaxAct = MaxDuty;
	if(MOTIONEN) Motion_Detected();
}

void SaveSettings(void)
{
	EEPROM_Config();
	EEPROM_ProgramByte(0,ID);
	EEPROM_ProgramByte(1,GroupID);
	EEPROM_ProgramByte(2,RampTime);
	EEPROM_ProgramByte(3,MaxDuty);
	EEPROM_ProgramByte(4,NightDuty);
	EEPROM_ProgramByte(5,Ch1Save);
	EEPROM_ProgramByte(6,Ch2Save);
	EEPROM_ProgramByte(7,Ch3Save);
	EEPROM_ProgramByte(8,RF_Motion_On_Time_10s);
	EEPROM_ProgramByte(9,MOTIONEN);
	//EEPROM_Program4Byte(10,EV1527_Stored_Codes[0]);
}

void SaveCodes (void)
{
	EEPROM_Program4Byte(10,EV1527_Stored_Codes[0]);
	EEPROM_Program4Byte(14,EV1527_Stored_Codes[1]);
	EEPROM_Program4Byte(18,EV1527_Stored_Codes[2]);
	EEPROM_Program4Byte(22,EV1527_Stored_Codes[3]);
}

void InitPWM(void)
{
	TIM2_DeInit ();
	TIM2_TimeBaseInit(TIM2_PRESCALER_64, 1000);  /* 1/frequency, count value 1000, frequency=2M/1000=2kHZ*/
	 /* PWM2 Mode configuration: Channel2 */
    if ((!EV1527 && !SWIM) && !PIR)
	{
	TIM2_OC2Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);
    TIM2_OC2PreloadConfig(ENABLE);
	}
	 /* PWM3 Mode configuration: Channel3*/
    TIM2_OC3Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_LOW);
    TIM2_OC3PreloadConfig(ENABLE);
	TIM2_ARRPreloadConfig (ENABLE);
	TIM2_Cmd(ENABLE);
	//PWM1 Init
	TIM1_DeInit();
    TIM1_TimeBaseInit(64, TIM1_COUNTERMODE_UP, 1000, 1);		//2M/1000=2kHz
    TIM1_OC3Init(TIM1_OCMODE_PWM2, 
                  TIM1_OUTPUTSTATE_ENABLE, 
                  TIM1_OUTPUTNSTATE_DISABLE, 
                  0, 
                  TIM1_OCPOLARITY_LOW, 
                  TIM1_OCNPOLARITY_LOW, 
                  TIM1_OCIDLESTATE_SET, 
                  TIM1_OCNIDLESTATE_RESET);
    TIM1_CtrlPWMOutputs(ENABLE);
    TIM1_Cmd(ENABLE);
	Ch1TGT = Ch1Save;
	Ch2TGT = Ch2Save;
	Ch3TGT = Ch3Save;
	Ch1Duty = 0; Ch2Duty=0;Ch3Duty=0;

}

void InitTIM4(void)
{
  TIM4->PSCR=0;				//1 frequency division, timer clock equals system clock = 16m

  TIM4->ARR=0XA0;			//10us reload value 0XA0

  TIM4->CNTR=0;				//It is necessary to clear down the counter
  TIM4->IER |= 1<<0;		//Enable tim4 update interrupt
  

  TIM4->SR1  |= 1<<0;		//Clear tim4 update interrupt flag

  TIM4->CR1 |= 1<<7;		//Allow reassembly to enable timer
  TIM4->CR1 |= 1<<0;		//Enabling tim4 counter
}

void Strobe_SWIM(uint8_t Num)
{
	uint8_t i;
	for (i=1;i<Num;i++)
	{
		TIM2_SetCompare3(gamma_lut[Ch1Save]);
		TIM1_SetCompare3(gamma_lut[Ch2Save]);
		_delay_ms(250);
		TIM2_SetCompare3(0);
		TIM1_SetCompare3(0);
		_delay_ms(250);
	}
	Ch1Duty = 0;
	Ch2Duty = 0;
	Ch3Duty = 0;
}

void RF_Task(void)
{
	uint8_t i = 0;
	uint8_t Command;
	if (EV1527_Valid_Code)
	{
		if (EV1527_Valid_Rec_Code == EV1527_Stored_Codes[0])	//Motion Detection code
		{
				Motion_Detected();
		}
		if (EV1527_Valid_Rec_Code == EV1527_Stored_Codes[1])	//Motion Detection code
		{
				Motion_Detected();
		}
		for (i = 2; i < 4; i++)
		{
			if ((EV1527_Valid_Rec_Code / 16) == (EV1527_Stored_Codes[i] / 16))
			{

				Command = EV1527_Valid_Rec_Code % 16;

				if (ValBit(Command, 0) != 0)
				{
					if (EV1527_Valid_Data)
					{
						if (EV1527_Valid_Rec_Data != 0)
						{
							Ch1TGT = EV1527_Valid_Rec_Data;
							Ch1Save = Ch1TGT;
							DutyChanged = TRUE;
							SaveSettings();
						}
					}
					else
					{
						Ch1TGT = Ch1Save;
						Manual_OVR = TRUE;
					}
					EV1527_Valid_Data = FALSE;
				}

				if (ValBit(Command, 0) == 0)
				{
					Ch1TGT = 0;
					Manual_OVR = FALSE;
				}

				if (ValBit(Command, 1) != 0)
				{
					if (EV1527_Valid_Data)
					{
						if (EV1527_Valid_Rec_Data != 0)
						{
							Ch2TGT = EV1527_Valid_Rec_Data;
							Ch2Save = Ch2TGT;
							DutyChanged = TRUE;
							SaveSettings();
						}
					}
					else
					{
						Ch2TGT = Ch2Save;
						Manual_OVR = TRUE;
					}
					EV1527_Valid_Data = FALSE;
				}

				if (ValBit(Command, 1) == 0)
				{
					Ch2TGT = 0;
					Manual_OVR = FALSE;
				}

				if (ValBit(Command, 2) != 0)
				{
					NIGHTMODEEN = TRUE;
					MaxAct = NightDuty;
					if (EV1527_Valid_Data)
					{
						NightDuty = EV1527_Valid_Rec_Data;
						SaveSettings();
						EV1527_Valid_Data = FALSE;
					}
				}
				if (ValBit(Command, 2) == 0)
				{
					NIGHTMODEEN = TRUE;
					MaxAct = MaxDuty;
				}

				if (ValBit(Command, 3) != 0)
				{
					MOTIONEN = TRUE;
					Manual_OVR = FALSE;
					Motion_Detected();
					if (EV1527_Valid_Data)
					{
						RF_Motion_On_Time_10s = EV1527_Valid_Rec_Data;
						SaveSettings();
						EV1527_Valid_Data = FALSE;
					}
				}
				if (ValBit(Command, 3) == 0)
				{
					MOTIONEN = FALSE;
				}
			}
			EV1527_Valid_Data = FALSE;
		}
	}
	EV1527_Valid_Code = FALSE;
}


void ParseSerial(void)
{
	
	if (serialbuff[0]!='P') return;
	if (serialbuff[6]!='\r') return;
	if ((serialbuff[1]==ID) || (serialbuff[1]==GroupID) || (serialbuff[1]==255)) 
	{
		if (serialbuff[2] == '1') 
		{
			EV1527_Stored_Codes[0] = (serialbuff[3]*65536) + (serialbuff[4]*256) + serialbuff[5];
			SaveCodes(); 
		}
		if (serialbuff[2] == '2') 
		{
			EV1527_Stored_Codes[1] = (serialbuff[3]*65536) + (serialbuff[4]*256) + serialbuff[5];
			SaveCodes(); 
		}
		if (serialbuff[2] == '3') 
		{
			EV1527_Stored_Codes[2] = (serialbuff[3]*65536) + (serialbuff[4]*256) + serialbuff[5];
			SaveCodes(); 
		}
		if (serialbuff[2] == '4') 
		{
			EV1527_Stored_Codes[3] = (serialbuff[3]*65536) + (serialbuff[4]*256) + serialbuff[5];
			SaveCodes(); 
		}
		if (serialbuff[2] == 'S')
		{
			switch (serialbuff[3])
			{
			case 'I':
				ID = serialbuff[4];
				break;
			case 'G':
				GroupID = serialbuff[4];
				break;
			case 'R':
				RampTime = serialbuff[4];
				break;
			case 'M':
				MaxDuty = serialbuff[4];
				break;
			case 'N':
				NightDuty = serialbuff[4];
				break;
			case 'T':
				RF_Motion_On_Time_10s = serialbuff[4];
				break;
			case 'E':
				if (serialbuff[4] == '1')
				{ 
					MOTIONEN = TRUE;
					Manual_OVR = FALSE;
					Motion_Detected();
				}
				if (serialbuff[4] == '0') MOTIONEN = FALSE;
				break;
			default:
				break;
			}
		SaveSettings();
		}
		if (serialbuff[2] == 'C')
		{
			switch (serialbuff[3])
			{
			case 'O':
				Ch1TGT = Ch1Save;
				Ch2TGT = Ch2Save;
				Ch3TGT = Ch3Save;
				Manual_OVR = TRUE;
				break;
			case 'F':
				Ch1TGT = 0;
				Ch2TGT = 0;
				Ch3TGT = 0;
				Manual_OVR = FALSE;
				break;
			case 'M':
				Motion_Detected();
				break;
			case 'N':
				if (serialbuff[4]=='1') 
				{
					NIGHTMODEEN = TRUE;
					MaxAct = NightDuty;
				}
				if (serialbuff[4]=='0') 
				{
					NIGHTMODEEN = FALSE;
					MaxAct = MaxDuty;
				}
				break;
			case '1':
				Ch1TGT = serialbuff[4];
				if (Ch1TGT!=0) Ch1Save = Ch1TGT;
				SaveSettings();
				break;
			case '2':
				Ch2TGT = serialbuff[4];
				if (Ch2TGT!=0) Ch2Save = Ch2TGT;
				SaveSettings();
				break;
			case '4':
				Ch3TGT = serialbuff[4];
				if (Ch3TGT!=0) Ch3Save = Ch3TGT;
				SaveSettings();
				break;
			case '3':
				Ch1TGT = serialbuff[4];
				Ch2TGT = serialbuff[5];
				if (Ch1TGT!=0) Ch1Save = Ch1TGT;
				if (Ch2TGT!=0) Ch2Save = Ch2TGT;
				SaveSettings();
				break;
			default:
				break;
			}
		}
	}
}



void SetPWM(void)
{
	Ramp1ms = 0;
	DutyChanged = FALSE;
	if ((Ch1Duty > Ch1TGT) || (Ch1Duty > MaxAct)) { Ch1Duty--; DutyChanged = TRUE; }
	if ((Ch2Duty > Ch2TGT) || (Ch2Duty > MaxAct)) { Ch2Duty--; DutyChanged = TRUE; }
	if ((Ch3Duty > Ch3TGT) || (Ch3Duty > MaxAct)) { Ch3Duty--; DutyChanged = TRUE; }
	if ((Ch1Duty < Ch1TGT) && (Ch1Duty < MaxAct)) { Ch1Duty++; DutyChanged = TRUE; }
	if ((Ch2Duty < Ch2TGT) && (Ch2Duty < MaxAct)) { Ch2Duty++; DutyChanged = TRUE; }
	if ((Ch3Duty < Ch3TGT) && (Ch3Duty < MaxAct)) { Ch3Duty++; DutyChanged = TRUE; }
	if (DutyChanged) 
	{
		TIM2_SetCompare3(gamma_lut[Ch1Duty]);
		TIM1_SetCompare3(gamma_lut[Ch2Duty]);
	}
	if ((!EV1527 && !SWIM) && !PIR) TIM2_SetCompare2(gamma_lut[Ch3Duty]);
}
void io_init(void)
{
	CLK->ICKR = CLK_ICKR_RESET_VALUE;
	CLK->ECKR = CLK_ECKR_RESET_VALUE;
	CLK->SWR = CLK_SWR_RESET_VALUE;
	CLK->SWCR = CLK_SWCR_RESET_VALUE;
	CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE;
	CLK->PCKENR1 = CLK_PCKENR1_RESET_VALUE;
	CLK->PCKENR2 = CLK_PCKENR2_RESET_VALUE;
	CLK->CSSR = CLK_CSSR_RESET_VALUE;
	CLK->CCOR = CLK_CCOR_RESET_VALUE;
	while ((CLK->CCOR & CLK_CCOR_CCOEN) != 0)
	{
	}
	CLK->CCOR = CLK_CCOR_RESET_VALUE;
	CLK->HSITRIMR = CLK_HSITRIMR_RESET_VALUE;
	CLK->SWIMCCR = CLK_SWIMCCR_RESET_VALUE; 			//CLK_DeInit();

	CLK->ECKR &= (uint8_t)(~CLK_ECKR_HSEEN); 			//CLK_HSECmd(DISABLE);
	CLK->ICKR &= (uint8_t)(~CLK_ICKR_LSIEN); 			//CLK_LSICmd(DISABLE);
	CLK->ICKR |= CLK_ICKR_HSIEN;			 			//CLK_HSICmd(ENABLE);
	CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
	CLK->CKDIVR |= (uint8_t)0x00; 						//CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
	CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_CPUDIV);
	CLK->CKDIVR |= (uint8_t)((uint8_t)0x80 & (uint8_t)CLK_CKDIVR_CPUDIV); //CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	disableInterrupts();
	GPIO_DeInit(GPIOA);
	GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST); // PWM3
	GPIO_DeInit(GPIOC);
	GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST); // PWM1
	GPIO_DeInit(GPIOB);
	GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);	//BTN
	GPIO_DeInit(GPIOD);
	GPIO_Init(GPIOD,GPIO_PIN_6,GPIO_MODE_IN_FL_IT);		//485Rx
	CONFIG_UNUSED_PINS_STM8S001;
	LoadSettings();
	InitTIM4();
	InitPWM();
	UART1_DeInit();
	UART1_Init(BAUDRATE,UART1_WORDLENGTH_8D,UART1_STOPBITS_1,UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_RX_ENABLE);
	UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);
	UART1_Cmd(ENABLE);
	if ((GPIOB->IDR & GPIO_PIN_4) == 0) { Strobe_SWIM(30); }		//If button pressed at startup stay at SWIM mode for 10s
	if (SWIM == FALSE)
	{
		//_delay_ms(7000);  //Wait 5s to turn off SWIM
		CFG->GCR |= 0x01; //disable SWIM interface
		if (EV1527)
		{
			GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_IT);
		} else if (PIR)
		{
			GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_FL_IT);
		}
		else
		{
			GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
		}
	}
	EXTI_DeInit();
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB,EXTI_SENSITIVITY_FALL_ONLY);
	if (EV1527 && !SWIM) 
		EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_RISE_FALL);
	if (PIR && !SWIM) 
		EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_RISE_ONLY);
	enableInterrupts();
}

void Timer_Task(void)
{
	
	//mS based Timer
	if (Timer_ms)
	{
		Timer_ms = FALSE;
		Timer_ms_to_s ++;
		//1 ms tasks
		

	}
	//Seconds based timer
	if (Timer_ms_to_s > 1000)
	{
		Timer_ms_to_s = 0;
		if (Motion_Active && !Manual_OVR)
		{
			Motion_On_Timer ++;
			if ((RF_Motion_On_Time_10s*10) < Motion_On_Timer)
			{
				Motion_Active = FALSE;
				Ch1TGT = 0;
				Ch2TGT = 0;
			}
		}
		//1s tasks
	}
	
	
}

main()
{
	io_init();
	
	
	while (1)
	{
		Timer_Task();
		if (bufflen==7) 
		{
			ParseSerial();
			bufflen = 0;
			UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);
		}
		if (Ramp1ms >= RampTime) SetPWM();
		if ((PIR && PIR_On) && MOTIONEN) 
		{
			Motion_Detected();
			PIR_On = FALSE;
		}
		if (EV1527 && !SWIM)
		{
			//EV1527_Receive_Parse();
			EV1527_Receive_Check();
			RF_Task();
			
		}
	}
}