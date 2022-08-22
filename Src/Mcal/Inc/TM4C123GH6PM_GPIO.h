/*
 * TM4C123GH6PM_GPIO.h
 *
 *  Created on: Aug 17, 2022
 *      Author: Bassant Ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TM4C123GH6PM_GPIO.h
 *       Module:  -GPIO
 *
 *  Description:  GPIO Driver for TM4C123GH6PM
 *
 *********************************************************************************************************************/


#ifndef SRC_MCAL_INC_TM4C123GH6PM_GPIO_H_
#define SRC_MCAL_INC_TM4C123GH6PM_GPIO_H_


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../Common/Std_Types.h"
#include "../../Common/Mcu_Hw.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	uint8 PortPinNumber;			//specifies the GPIO pin Number to be configured.
									//this parameter must be set based on a value @ref Port_PinNum_define

	uint8 PortPinMode ;			//specifies the GPIO pin Mode to be configured.
									//this parameter must be set based on a value @ref Port_PinMode_define

	uint8 PortPinLevelValue ;		//specifies the GPIO pin Level to be configured.
									//this parameter must be set based on a value @ref Port_PinLevel_define

	uint8 PortPinDirection ;		//specifies the GPIO pin Direction to be configured.
									//this parameter must be set based on a value @ref Port_PinDir_define

	uint8 PortPinInternalAttach ;	//specifies the GPIO pin internal pull up or pull down attach to be configured.
									//this parameter must be set based on a value @ref Port_PinAttach_define

	uint8 PortPinOutputCurrent ;	//specifies the GPIO pin output current to be configured.
									//this parameter must be set based on a value @ref Port_PinOutCurrent_define

}Port_ConfigType;

typedef enum
{
	Low,
	High
}Dio_LevelType;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref Port_PinNum_define
//#define 	Port_PinNum_0				0x01			//(1<<0)
//#define 	Port_PinNum_1				0x02			//(1<<1)
//#define 	Port_PinNum_2				0x04			//(1<<2)
//#define 	Port_PinNum_3				0x08			//(1<<3)
//#define 	Port_PinNum_4				0x10			//(1<<4)
//#define 	Port_PinNum_5				0x20			//(1<<5)
//#define 	Port_PinNum_6				0x40			//(1<<6)
//#define 	Port_PinNum_7				0x80			//(1<<7)
typedef enum
{
	Pin0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7
}Dio_ChannelType;

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

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void port_init (GPIO_TypeDef * GPIOx, Port_ConfigType* ConfigPtr);
Dio_LevelType Dio_ReadChannel (GPIO_TypeDef * GPIOx,Dio_ChannelType ChannelId);
void Dio_WriteChannel (GPIO_TypeDef * GPIOx,Dio_ChannelType ChannelId,Dio_LevelType Level );
uint8 Dio_ReadPort (GPIO_TypeDef * GPIOx);
void Dio_WritePort (GPIO_TypeDef * GPIOx,uint8 Level );
Dio_LevelType Dio_FlipChannel (GPIO_TypeDef * GPIOx,Dio_ChannelType ChannelId);


#endif /* SRC_MCAL_INC_TM4C123GH6PM_GPIO_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
