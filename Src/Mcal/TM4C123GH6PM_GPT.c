/*
 * TM4C123GH6PM_GPT.c
 *
 *  Created on: Aug 21, 2022
 *      Author: Bassant Ahmed
 */
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief
 *
 *      \details
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Inc/TM4C123GH6PM_GPT.h"
#include "Inc/TM4C123GH6PM_GPIO.h"
#include "../Common/Mcu_Hw.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
uint32 Get_Port_GPT (Dio_ChannelType Port)
{
	switch ((uint8)Port/8)
	{
	case 0:	//PortB
		return (uint32)GPIOB_Base;
		break;

	case 1: //PortC
		return (uint32)GPIOC_Base;
		break;

	case 2: //PortD
		return (uint32)GPIOD_Base;
		break;

	case 3: //PortF
		return (uint32)GPIOF_Base;
		break;
	}
}

PinNum Get_Pin_GPT (Dio_ChannelType Pin)
{
	uint8 pinx = Pin % 8;
	switch (pinx)
	{
	case 0:	//Pin0
		return Pin0;
		break;

	case 1: //Pin1
		return Pin1;
		break;

	case 2: //Pin2
		return Pin2;
		break;

	case 3: //Pin3
		return Pin3;
		break;

	case 4: //Pin4
		return Pin4;
		break;

	case 5: //Pin5
		return Pin5;
		break;

	case 6: //Pin6
		return Pin6;
		break;

	case 7: //Pin7
		return Pin7;
		break;
	}
}
GPT_TypeDef * CLK_AF_Enable (GPT_TimerType Timer, uint32 Portx , uint8 Pinx)
{
	GPIO_TypeDef* PortPtr = Portx;
	if ((Timer/6)==0)
	{
		switch (Timer % 6)
		{
		case 0 :
			GPTTimer16_0_CLK_EN();
			return Timer0_16;
			break;
		case 1:
			GPTTimer16_1_CLK_EN();
			return Timer1_16;
			break;
		case 2:
			GPTTimer16_2_CLK_EN();
			return Timer2_16;
			break;
		case 3:
			GPTTimer16_3_CLK_EN();
			return Timer3_16;
			break;
		case 4:
			GPTTimer16_4_CLK_EN();
			return Timer4_16;
			break;
		case 5:
			GPTTimer16_5_CLK_EN();
			return Timer5_16;
			break;
		}
	}
	else if ((Timer/6)==1)
	{
		switch (Timer % 6)
		{
		case 0 :
			GPTTimer32_0_CLK_EN();
			return Timer0_32;
			break;
		case 1:
			GPTTimer32_1_CLK_EN();
			return Timer1_32;
			break;
		case 2:
			GPTTimer32_2_CLK_EN();
			return Timer2_32;
			break;
		case 3:
			GPTTimer32_3_CLK_EN();
			return Timer3_32;
			break;
		case 4:
			GPTTimer32_4_CLK_EN();
			return Timer4_32;
			break;
		case 5:
			GPTTimer32_5_CLK_EN();
			return Timer5_32;
			break;
		}
	}

	if (Portx == GPIOB_Base)
		GPIOB_CLK_EN();
	else if (Portx == GPIOC_Base)
		GPIOC_CLK_EN();
	else if (Portx == GPIOD_Base)
		GPIOD_CLK_EN();
	else if (Portx == GPIOF_Base)
		GPIOA_CLK_EN();

	//make the pin AF to the timer
	Set_bit_GPIO(Portx ,Pinx , GPIOAFSEL_offset);
	switch (Pinx)
	{
	case 0:
		PortPtr->GPIOPCTL.B.PMC0 = 7;
		break;
	case 1:
		PortPtr->GPIOPCTL.B.PMC1 = 7;
		break;
	case 2:
		PortPtr->GPIOPCTL.B.PMC2 = 7;
		break;
	case 3:
		PortPtr->GPIOPCTL.B.PMC3 = 7;
		break;
	case 4:
		PortPtr->GPIOPCTL.B.PMC4 = 7;
		break;
	case 5:
		PortPtr->GPIOPCTL.B.PMC5 = 7;
		break;
	case 6:
		PortPtr->GPIOPCTL.B.PMC6 = 7;
		break;
	case 7:
		PortPtr->GPIOPCTL.B.PMC7 = 7;
		break;
	}
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void GPT_init(GPT_ConfigType* ConfigPtr)
{
	GPT_TypeDef * TimerPtr;
	uint32 Portx = Get_Port_GPT(ConfigPtr->ChannelID);
	GPIO_TypeDef* PortPtr = Portx;
	uint8 Pinx = Get_Pin_GPT(ConfigPtr->ChannelID);
	uint32 * ConfigReg ;

	//Enable the clock and set the AF Pin to timer pin
	TimerPtr = CLK_AF_Enable (ConfigPtr->GPTTimerType,Portx ,Pinx);

	//Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes.
	if (!(TimerPtr->GPTMCTL.B.TAEN || TimerPtr->GPTMCTL.B.TBEN))
	{
		//Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
		TimerPtr->GPTMCFG = 0;

		//Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
		TimerPtr->GPTMTAMR.B.TAMR = ConfigPtr->ChannelMode;

		//set individual mode if needed
		if (((ConfigPtr->GPTChannelTickMax < 0xFFFF)&& (ConfigPtr->GPTTimerType/6 == 0)) || ((ConfigPtr->GPTChannelTickMax < 0xFFFFFFFF) && (ConfigPtr->GPTTimerType/6 == 1)))
			TimerPtr->GPTMCFG |= (0x4 <<0);



		//If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register (GPTMIMR).
		TimerPtr->GPTMIMR |= (1<<4);

	}


}


void GPT_DisableNotification (GPT_ChannelType Channel)
{

}


void GPT_EnableNotification (GPT_ChannelType Channel)
{

}


void GPT_StartTimer ()
{
//Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).

	//Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.


	/*Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
	the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
	Register (GPTMICR).*/
}


void GPT_StopTimer ()
{

}


void GPT_SetMode ()
{

}


/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
