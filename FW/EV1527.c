#include "EV1527.h"

const uint8_t EV1527_Learn_Count_Min = 10;
const uint8_t EV1527_PulseTime_Nominal_10us = 35;
const uint8_t EV1527_PulseTime_Max_10us = 45;
const uint8_t EV1527_PulseTime_Min_10us = 28;
const uint16_t EV1527_Pulse_Timeout_10us = EV1527_PulseTime_Max_10us * 35;
const uint16_t EV1527_Packet_Repeat_Timeout_10us = EV1527_PulseTime_Max_10us * 500;
const uint16_t EV1527_Sync_Low_Max_10us = EV1527_PulseTime_Max_10us * 31;
const uint16_t EV1527_Sync_Low_Min_10us = EV1527_PulseTime_Min_10us * 31;
const uint16_t EV1527_3_PulseTime_Max_10us = EV1527_PulseTime_Max_10us * 3;
const uint16_t EV1527_3_PulseTime_Min_10us = EV1527_PulseTime_Min_10us * 3;


extern uint32_t EV1527_Rec_Code;
extern uint32_t EV1527_Valid_Rec_Code;
extern uint8_t EV1527_Rec_Data;
extern uint8_t EV1527_Valid_Rec_Data;
extern uint8_t EV1527_Repeat_Count;
extern bool EV1527_Valid_Code;
extern bool EV1527_Valid_Learn_Code;
extern bool EV1527_Valid_Data;
extern volatile uint16_t EV1527_Hightime;
extern volatile uint16_t EV1527_LowTime;
extern volatile bool EV1527_BitReady;
extern uint32_t EV1527_Transmit_Data;

bool EV1527_sync_OK;
//extern bool EV1527_edge_type;
//extern bool EV1527_last_edge_type;
//extern uint16_t EV1527_edge_time_10us;
//extern uint16_t Last_edge_time_10us;


uint8_t EV1527_bit_count;
extern volatile uint16_t Timer_last_valid_packet_10us;
extern volatile uint16_t Timer_last_edge_10us;


void EV1527_Receive_Parse(void)
{
    if (EV1527_BitReady)
    {
        if ((EV1527_Hightime > EV1527_PulseTime_Min_10us) && (EV1527_Hightime < EV1527_PulseTime_Max_10us) &&
            (EV1527_LowTime > EV1527_Sync_Low_Min_10us) && (EV1527_LowTime < EV1527_Sync_Low_Max_10us))
        {
            if (EV1527_sync_OK)
            {
                if (EV1527_bit_count == 24)
                {
                    if (EV1527_Repeat_Count ==0)
                    {
                        EV1527_Valid_Rec_Code = EV1527_Rec_Code;
                        EV1527_Repeat_Count++;
                    }
                    if (EV1527_Repeat_Count >=1) 
                    {
                        if (EV1527_Rec_Code == EV1527_Valid_Rec_Code)
                        { 
                            EV1527_Repeat_Count++;
                        } else
                        {
                            EV1527_Valid_Rec_Code = EV1527_Rec_Code;
                            EV1527_Repeat_Count = 1;
                        }
                        
                    }
                    if (EV1527_Repeat_Count == 2)
                    {
                        EV1527_Valid_Code = TRUE;
                        EV1527_Valid_Data = FALSE;
                    }
                    if (EV1527_Repeat_Count == EV1527_Learn_Count_Min) 
                    {
                        EV1527_Valid_Learn_Code = TRUE;
                    }
                    Timer_last_valid_packet_10us = 0;
					EV1527_bit_count = 0;
                    EV1527_Rec_Code = 0;
                }
                else if (EV1527_bit_count == 32)
                {
                    if (EV1527_Repeat_Count ==0)
                    {
                        EV1527_Valid_Rec_Code = EV1527_Rec_Code;
                        EV1527_Valid_Rec_Data = EV1527_Rec_Data;
                        EV1527_Repeat_Count++;
                    }
                    if ((EV1527_Repeat_Count >=1) && (EV1527_Rec_Code == EV1527_Valid_Rec_Code) && (EV1527_Rec_Data == EV1527_Valid_Rec_Data))
                    {
                        EV1527_Repeat_Count++;
                    }
                    if (EV1527_Repeat_Count == 2)
                    {
                        EV1527_Valid_Code = TRUE;
                        EV1527_Valid_Data = TRUE;
                    }
                    if (EV1527_Repeat_Count == EV1527_Learn_Count_Min)
                    { 
                        EV1527_Valid_Learn_Code = TRUE;
                    }
                    Timer_last_valid_packet_10us = 0;
                    EV1527_bit_count = 0;
                    EV1527_Rec_Code = 0;
                    EV1527_Rec_Data = 0;
                }
                else
                {
                    EV1527_Rec_Code = 0;
                    EV1527_Rec_Data = 0;
                    
                    EV1527_bit_count = 0;
                    Timer_last_valid_packet_10us = 0;
                    
                }
            }
            else
            {
                EV1527_sync_OK = TRUE;
            }
        }

        if (EV1527_sync_OK)
        {
            // Bit 0
            if ((EV1527_Hightime > EV1527_PulseTime_Min_10us) && (EV1527_Hightime < EV1527_PulseTime_Max_10us) &&
                (EV1527_LowTime > EV1527_3_PulseTime_Min_10us) && (EV1527_LowTime < EV1527_3_PulseTime_Max_10us))
            {
                if (EV1527_bit_count < 24)
                {
                    EV1527_Rec_Code <<= 1;
                }
                else if (EV1527_bit_count < 32)
                {
                    EV1527_Rec_Data <<= 1;
                }
                EV1527_bit_count++;
            }
            //bit 1
            else if ((EV1527_LowTime > EV1527_PulseTime_Min_10us) && (EV1527_LowTime < EV1527_PulseTime_Max_10us) &&
                     (EV1527_Hightime > EV1527_3_PulseTime_Min_10us) && (EV1527_Hightime < EV1527_3_PulseTime_Max_10us))
            {
                if (EV1527_bit_count < 24)
                {
                    EV1527_Rec_Code <<= 1;
                    EV1527_Rec_Code++;
                }
                else if (EV1527_bit_count < 32)
                {
                    EV1527_Rec_Data <<= 1;
                    EV1527_Rec_Data++;
                }
                EV1527_bit_count++;
            }
        }
        EV1527_BitReady = FALSE;
        EV1527_Hightime = 0;
    }
}

void EV1527_Receive_Check(void)
{   
    if ((Timer_last_valid_packet_10us > EV1527_Packet_Repeat_Timeout_10us) && (EV1527_Valid_Code == FALSE))
    {
        nop();
		EV1527_sync_OK = FALSE;
        EV1527_bit_count = 0;
	    EV1527_Repeat_Count = 0;
        EV1527_Rec_Code = 0;
        EV1527_Rec_Data = 0;
        EV1527_Valid_Rec_Code = 0;
    }

}  