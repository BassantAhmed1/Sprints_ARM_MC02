/*
 * TM4C123GH6PM_GPIO.c
 *
 *  Created on: Aug 17, 2022
 *      Author: Bassant Ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**     \file  TM4C123GH6PM_GPIO.c
 *      \brief
 *
 *      \details
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
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
 * \Syntax          : void port_init (const Port_ConfigType* ConfigPtr)
 * \Description     : initializing the specified port
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void port_init (GPIO_TypeDef * GPIOx , Port_ConfigType* ConfigPtr)
{
	//Enable the clock
	if ((uint32)GPIOx == GPIOA_Base)
		GPIOA_CLK_EN();
	else if ((uint32)GPIOx == GPIOB_Base)
		GPIOB_CLK_EN();
	else if ((uint32)GPIOx == GPIOC_Base)
		GPIOC_CLK_EN();
	else if ((uint32)GPIOx == GPIOD_Base)
		GPIOD_CLK_EN();
	else if ((uint32)GPIOx == GPIOE_Base)
		GPIOE_CLK_EN();
	else if ((uint32)GPIOx == GPIOF_Base)
		GPIOA_CLK_EN();



	//Set the direction of the GPIO port pins by programming the GPIODIR register.
	if (ConfigPtr->PortPinDirection == Port_PinDir_Input)
		Clear_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIODIR_offset);
	else
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIODIR_offset);

	//Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin
	if (ConfigPtr->PortPinMode == Port_PinMode_GPIO)
		Clear_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIOAFSEL_offset);
	else
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIOAFSEL_offset);

	//Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8R registers
	switch (ConfigPtr->PortPinOutputCurrent)
	{
	case Port_PinOutCurrent_2mA :
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIODR2R_offset);
		break;
	case Port_PinOutCurrent_4mA :
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIODR4R_offset);
		break;
	case Port_PinOutCurrent_8mA :
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIODR8R_offset);
		break;
	}

	//Program each pad in the port to have either pull-up, pull-down, or open drain functionality through
	//the GPIOPUR, GPIOPDR, GPIOODR register.
	switch (ConfigPtr->PortPinInternalAttach)
	{
	case Port_PinAttach_PU :
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIOPUR_offset);
		break;
	case Port_PinAttach_PD :
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIOPDR_offset);
		break;
	case Port_PinAttach_OD :
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIOODR_offset);
		break;
	}

	if (ConfigPtr->PortPinLevelValue == Port_PinLevel_High)
		Set_bit_GPIO((uint32)GPIOx ,ConfigPtr->PortPinNumber , GPIODATA_offset);

}

/******************************************************************************
 * \Syntax          : Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
Dio_LevelType Dio_ReadChannel (GPIO_TypeDef * GPIOx,Dio_ChannelType ChannelId)
{
	if((GPIOx->GPIODATA & (1<<ChannelId))==1)
		return 1;
	else
		return 0;
}

/******************************************************************************
 * \Syntax          : void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Dio_WriteChannel (GPIO_TypeDef * GPIOx,Dio_ChannelType ChannelId,Dio_LevelType Level )
{
	if (Level == High)
		Set_bit_GPIO((uint32)GPIOx ,ChannelId , GPIODATA_offset);
	else
		Clear_bit_GPIO((uint32)GPIOx ,ChannelId , GPIODATA_offset);
}

/******************************************************************************
 * \Syntax          : Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
uint8 Dio_ReadPort (GPIO_TypeDef * GPIOx)
{
	return (uint8)GPIOx->GPIODATA ;
}

/******************************************************************************
 * \Syntax          : void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Dio_WritePort (GPIO_TypeDef * GPIOx,uint8 Level )
{
	GPIOx->GPIODATA = Level;
}

/******************************************************************************
 * \Syntax          : Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
//Dio_LevelType Dio_FlipChannel (GPIO_TypeDef * GPIOx,Dio_ChannelType ChannelId)
//{

//}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
