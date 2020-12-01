#ifndef __SETTINGS_H
#define __SETTINGS_H

#define CONFIG_UNUSED_PINS_STM8S001 \
{ \
 GPIOA->DDR |= GPIO_PIN_2; \
 GPIOB->DDR |= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6 | GPIO_PIN_7; \
 GPIOC->DDR |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7; \
 GPIOD->DDR |= GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_7; \
 GPIOE->DDR |= GPIO_PIN_5; \
 GPIOF->DDR |= GPIO_PIN_4; \
}

#define F_CPU 16000000UL
#define T_COUNT(x) (( F_CPU * x / 1000000UL )-3)/3
#define BAUDRATE 57600
#define SWIM FALSE
#define PIR	FALSE
#define EV1527 TRUE

// PIN1 UART1_Rx
// PIN5 PA3 TIM2CH3 //PWM1
// PIN6 PB4 BTN Input.
// PIN7 PC3 TIM1CH3 //PWM2
// PIN8 SWIM / PD3 TIM2CH2	//PWM3 or RfRx or PIR

/*
Serial Protocol 7 Bytes byte7 is \r
Byte 1 					2					3					4					5					6
P (PWM Control)			ID					1(RF Code)			Byte3				Byte2               Byte1                   //RF Code Store 
P (PWM Control)			ID					2(RF Code)			Byte3				Byte2               Byte1                   //RF Code Store 
P (PWM Control)			ID					3(RF Code)			Byte3				Byte2               Byte1                   //RF Code Store 
P (PWM Control)			ID					4(RF Code)			Byte3				Byte2               Byte1                   //RF Code Store 								  
P (PWM Control)			ID					S(settings)			I(ID)				ID											//Individual ID 1-100
P (PWM Control)			ID					S(settings)			G(GroupID)			GroupID										//Group ID 101-
P (PWM Control)			ID					S(settings)			R(Ramp Time)		Time(x100ms)								//Ramp Time to 100%
P (PWM Control)			ID					S(settings)			M(max)				Max Duty
P (PWM Control)			ID					S(settings)			N(Night Mode)		Night Duty
P (PWM Control)			ID					S(settings)			T(Motion ON Time)	Time(x10s)
P (PWM Control)			ID					S(settings)			E(Motion Enable)	BOOL 										//'1'/'0'

P (PWM Control)			ID					C(control)			O(On)
P (PWM Control)			ID					C(control)			F(Off)
P (PWM Control)			ID					C(control)			M(Motion Det)
P (PWM Control)			ID					C(control)			N(Night Mode)		BOOL
P (PWM Control)			ID					C(control)			1(Channel 1)		Duty
P (PWM Control)			ID					C(control)			2(Channel 2)		Duty
P (PWM Control)			ID					C(control)			4(Channel 3)		Duty
P (PWM Control)			ID					C(control)			3(Channel 1,2)		Duty1				Duty2
*/

/*
RF Control
bit 4                   3                   2                   1                   byte4
Motion Enable                                                                       x
                        Night Enable                                                Night Duty
                                            CH2                                     CH2 Duty
                                                                CH1                 CH1 Duty
*/
#endif