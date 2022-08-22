/*
 * main.c
 *
 *  Created on: Aug 18, 2022
 *      Author: Bassant Ahmed
 */


#include "../Mcal/Inc/TM4C123GH6PM_GPIO.h"
#include "../Common/Mcu_Hw.h"


void GPIO_init(void){
	Port_ConfigType PortConfig;
	PortConfig.PortPinNumber =Pin1;
	PortConfig.PortPinDirection = Port_PinDir_Output;
	PortConfig.PortPinInternalAttach = Port_PinAttach_PU;
	PortConfig.PortPinLevelValue = Port_PinLevel_High;
	PortConfig.PortPinMode = Port_PinMode_GPIO;
	PortConfig.PortPinOutputCurrent = Port_PinOutCurrent_2mA;

	port_init(GPIOA , &PortConfig);
}

int main(void)
{
	GPIO_init();
	while(1)
	{



	}
}
