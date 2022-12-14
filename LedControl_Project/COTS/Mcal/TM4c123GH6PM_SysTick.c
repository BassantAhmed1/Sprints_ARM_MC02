/*
 * TM4c123GH6PM_SysTick.c
 *
 *  Created on: Aug 29, 2022
 *      Author: Bassant Ahmed
 */


#include "../Common/Std_Types.h"
#include "Inc/TM4c123GH6PM_SysTick.h"
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
void SysTick_init (void)
{

	STCTRL =0;
	STCTRL |= (1<<2) ;

	if (STConfig.IRQEnable)
			STCTRL |= (1<<1) ;
		else
			STCTRL &= ~(1<<1) ;
	STCURRENT = 0;
}



void StartSysTick (uint32 Seconds_ms)
{
	STCTRL |= (1<<1);
	uint32 counts = 16000000/(1000 /Seconds_ms);		//16MHZ

	STRELOAD = (uint32)(counts - 1);

	STCTRL |= (1<<0);		//STCTRL->B.Enable
}

void StopSysTick (void)
{
	STCTRL &= ~(1<<0);		//STCTRL->B.Enable
	STCTRL &= ~(1<<1);		//STCTRL->B.INTEN = IRQ_Disable;
}

void SysTick_Handler(void)
{
	Dio_FlipChannel(Dio_PortF_PF1);
	StopSysTick();

}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
