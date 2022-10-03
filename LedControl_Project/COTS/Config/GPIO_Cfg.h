/*
 * GPIO_Cfg.h
 *
 *  Created on: Aug 30, 2022
 *      Author: Bassant Ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPIO_Cfg.h
 *       Module:  -GPIO
 *
 *  Description:  in this file there's the references and APIs for the user
 *
 *********************************************************************************************************************/

#ifndef SRC_CONFIG_GPIO_CFG_H_
#define SRC_CONFIG_GPIO_CFG_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../Common/Std_Types.h"
#include "../Common/Mcu_Hw.h"
#include "../Mcal/Inc/TM4C123GH6PM_GPIO.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref Port_PinMode_define
#define		Port_PinMode_GPIO			0
#define		Port_PinMode_AF				1

//@ref Port_PinLevel_define
#define 	Port_PinLevel_Low			0
#define 	Port_PinLevel_High			1

//@ref Port_PinDir_define
#define 	Port_PinDir_Input			0
#define 	Port_PinDir_Output			1


//@ref Port_PinAttach_define
#define 	Port_PinAttach_PU			0
#define 	Port_PinAttach_PD			1
#define 	Port_PinAttach_OD			2

//@ref Port_PinOutCurrent_define
#define 	Port_PinOutCurrent_2mA		0
#define 	Port_PinOutCurrent_4mA		1
#define 	Port_PinOutCurrent_8mA		2


//------------------------------------------------------------------------------------------------------------------



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void port_init (Port_ConfigType* ConfigPtr);
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level );
uint8 Dio_ReadPort (GPIO_TypeDef * GPIOx);
void Dio_WritePort (GPIO_TypeDef * GPIOx,uint8 Data );
void Dio_FlipChannel (Dio_ChannelType ChannelId);


#endif /* SRC_CONFIG_GPIO_CFG_H_ */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.h
 *********************************************************************************************************************/
