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
uint32 Get_Port (Dio_ChannelType Port)
{
	switch ((uint8)Port/8)
	{
	case 0:	//PortA
		return (uint32)GPIOA_Base;
		break;

	case 1: //PortB
		return (uint32)GPIOB_Base;
		break;

	case 2: //PortC
		return (uint32)GPIOC_Base;
		break;

	case 3: //PortD
		return (uint32)GPIOD_Base;
		break;

	case 4: //PortE
		return (uint32)GPIOE_Base;
		break;

	case 5: //PortF
		return (uint32)GPIOF_Base;
		break;
	}
}

PinNum Get_Pin (Dio_ChannelType Pin)
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
void port_init (Port_ConfigType* ConfigPtr)
{
	uint32 Portx = Get_Port(ConfigPtr->PortPinType);
	PinNum Pinx = Get_Pin(ConfigPtr->PortPinType);

	//Enable the clock
	if (Portx == GPIOA_Base)
		{GPIOA_CLK_EN();}
	else if (Portx == GPIOB_Base)
		{GPIOB_CLK_EN();}
	else if (Portx == GPIOC_Base)
		{GPIOC_CLK_EN();}
	else if (Portx == GPIOD_Base)
		{GPIOD_CLK_EN();}
	else if (Portx == GPIOE_Base)
		{GPIOE_CLK_EN();}
	else if (Portx == GPIOF_Base)
		{GPIOF_CLK_EN();}



	//Set the direction of the GPIO port pins by programming the GPIODIR register.
	if (ConfigPtr->PortPinDirection == Port_PinDir_Input)
		Clear_bit_GPIO(Portx ,Pinx, GPIODIR_offset);
	else
		Set_bit_GPIO(Portx ,Pinx , GPIODIR_offset);

	//Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin
	if (ConfigPtr->PortPinMode == Port_PinMode_GPIO)
		Clear_bit_GPIO(Portx ,Pinx , GPIOAFSEL_offset);
	else
		Set_bit_GPIO(Portx ,Pinx , GPIOAFSEL_offset);

	//Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8R registers
	switch (ConfigPtr->PortPinOutputCurrent)
	{
	case Port_PinOutCurrent_2mA :
		Set_bit_GPIO(Portx ,Pinx , GPIODR2R_offset);
		break;
	case Port_PinOutCurrent_4mA :
		Set_bit_GPIO(Portx ,Pinx , GPIODR4R_offset);
		break;
	case Port_PinOutCurrent_8mA :
		Set_bit_GPIO(Portx ,Pinx , GPIODR8R_offset);
		break;
	}

	//Program each pad in the port to have either pull-up, pull-down, or open drain functionality through
	//the GPIOPUR, GPIOPDR, GPIOODR register.
	switch (ConfigPtr->PortPinInternalAttach)
	{
	case Port_PinAttach_PU :
		Set_bit_GPIO(Portx ,Pinx , GPIOPUR_offset);
		break;
	case Port_PinAttach_PD :
		Set_bit_GPIO(Portx ,Pinx , GPIOPDR_offset);
		break;
	case Port_PinAttach_OD :
		Set_bit_GPIO(Portx ,Pinx , GPIOODR_offset);
		break;
	}

	//Enable DEN
	Set_bit_GPIO(Portx ,Pinx , GPIODEN_offset);

	if (ConfigPtr->PortPinLevelValue == Port_PinLevel_High)
		Set_bit_GPIO(Portx ,Pinx , GPIODATA_offset);

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
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId)
{
	GPIO_TypeDef * Portx = Get_Port(ChannelId);
	PinNum Pinx = Get_Pin(ChannelId);

	if((Portx->GPIODATA & (1<<Pinx))==1)
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
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level )
{
	GPIO_TypeDef * Portx = Get_Port(ChannelId);
	PinNum Pinx = Get_Pin(ChannelId);
	volatile uint32 * GPIODATAPtr = Portx->GPIODATA + (0b10<<2);

	if (Level == High)
		*GPIODATAPtr |= (1<<Pinx);
	else
		*GPIODATAPtr &= ~(1<<Pinx);
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
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId)
{
	uint32 Portx = Get_Port(ChannelId);
	PinNum Pinx = Get_Pin(ChannelId);

	if (Dio_ReadChannel (ChannelId) == Low)
		Set_bit_GPIO(Portx ,Pinx , (GPIODATA_offset));
	else
		Clear_bit_GPIO(Portx ,Pinx , GPIODATA_offset);
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
