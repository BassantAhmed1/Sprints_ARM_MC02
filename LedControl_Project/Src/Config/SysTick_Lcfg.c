/*
 * SysTick_Lcfg.c
 *
 *  Created on: Aug 30, 2022
 *      Author: Bassant Ahmed
 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../Common/Std_Types.h"
#include "../Common/Mcu_Hw.h"
#include "../Mcal/Inc/TM4c123GH6PM_SysTick.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
SysTick_ConfigType STConfig = {
		System_CLK,				//@ref SystTick_ClkSrc_Define
		IRQ_Enable				//@ref IR_Enable_Define
};




/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Lcfg.c
 *********************************************************************************************************************/



