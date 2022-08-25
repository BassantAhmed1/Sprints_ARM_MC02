/*
 * TM4C123GH6PM_GPT.h
 *
 *  Created on: Aug 21, 2022
 *      Author: Bassant Ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TM4C123GH6PM_GPT.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/

#ifndef SRC_MCAL_INC_TM4C123GH6PM_GPT_H_
#define SRC_MCAL_INC_TM4C123GH6PM_GPT_H_


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../Common/Std_Types.h"
#include "../../Common/Mcu_Hw.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define GPT_Freq_Define		GPT_Freq_16MHZ

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


typedef enum
{
	Timer0_16_,
	Timer1_16_,
	Timer2_16_,
	Timer3_16_,
	Timer4_16_,
	Timer5_16_,

	Timer0_32_,
	Timer1_32_,
	Timer2_32_,
	Timer3_32_,
	Timer4_32_,
	Timer5_32_
}GPT_TimerType;

typedef enum
{
	GPT_ChannelMode_OneShot =1,
	GPT_ChannelMode_Continous

}GPT_ModeType;

typedef enum
{
	GPT_PortB_PB0,
	GPT_PortB_PB1,
	GPT_PortB_PB2,
	GPT_PortB_PB3,
	GPT_PortB_PB4,
	GPT_PortB_PB5,

	GPT_PortC_PC0 =8,
	GPT_PortC_PC1,
	GPT_PortC_PC2,
	GPT_PortC_PC3,
	GPT_PortC_PC4,
	GPT_PortC_PC5,
	GPT_PortC_PC6,
	GPT_PortC_PC7,

	GPT_PortD_PD0,
	GPT_PortD_PD1,
	GPT_PortD_PD2,
	GPT_PortD_PD3,
	GPT_PortD_PD4,
	GPT_PortD_PD5,
	GPT_PortD_PD6,
	GPT_PortD_PD7,

	GPT_PortF_PF2,
	GPT_PortF_PF3,
	GPT_PortF_PF4
}GPT_ChannelType;


typedef struct
{
	GPT_TimerType 		GPTTimerType;
	GPT_ChannelType 	ChannelID;
	uint32				GPTChannelTickFreq;
	uint32				GPTChannelTickMax;
	GPT_ModeType		ChannelMode;
	void (* NotificationPtr) (GPT_ChannelType Channel);


}GPT_ConfigType;



//-----------------------------
//Macros Configuration References
//-----------------------------


//@ref GPT_Freq_Define

#define GPT_Freq_16MHZ		0xF42400
#define GPT_Freq_8MHZ		0x7A1200
#define GPT_Freq_4MHZ		0x3D0900
#define GPT_Freq_2MHZ		0x1E8480
#define GPT_Freq_1MHZ		0xF4240

//------------------------------------------------------------------------------------------------------------------

#define Count_Dir_down		0
#define Count_Dir_up		1


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void GPT_init(GPT_ConfigType* ConfigPtr);
void GPT_DisableNotification (GPT_ChannelType Channel);
void GPT_EnableNotification (GPT_ChannelType Channel);
void GPT_StartTimer (uint8 Seconds_ms);
void GPT_StopTimer ();
void GPT_SetMode ();

#endif /* SRC_MCAL_INC_TM4C123GH6PM_GPT_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
