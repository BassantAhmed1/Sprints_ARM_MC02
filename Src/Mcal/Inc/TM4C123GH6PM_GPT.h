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
	T2CCP0_PortB_PB0,
	T2CCP1_PortB_PB1,
	T3CCP0_PortB_PB2,
	T3CCP1_PortB_PB3,
	T1CCP0_PortB_PB4,
	T1CCP1_PortB_PB5,
	T0CCP0_PortB_PB6,
	T0CCP1_PortB_PB7,

	T4CCP0_PortC_PC0,
	T4CCP1_PortC_PC1,
	T5CCP0_PortC_PC2,
	T5CCP1_PortC_PC3,
	WT0CCP0_PortC_PC4,
	WT0CCP1_PortC_PC5,
	WT1CCP0_PortC_PC6,
	WT1CCP1_PortC_PC7,

	WT2CCP0_PortD_PD0,
	WT2CCP1_PortD_PD1,
	WT3CCP0_PortD_PD2,
	WT3CCP1_PortD_PD3,
	WT4CCP0_PortD_PD4,
	WT4CCP1_PortD_PD5,
	WT5CCP0_PortD_PD6,
	WT5CCP1_PortD_PD7,

	T0CCP0_PortF_PF0,
	T0CCP1_PortF_PF1,
	T1CCP0_PortF_PF2,
	T1CCP1_PortF_PF3,
	T2CCP0_PortF_PF4
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
 *  END OF FILE: TM4C123GH6PM_GPT.h
 *********************************************************************************************************************/
