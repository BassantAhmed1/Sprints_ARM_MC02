/*
 * main.c
 *
 *  Created on: Aug 18, 2022
 *      Author: Bassant Ahmed
 */


#include "../Mcal/Inc/TM4C123GH6PM_GPIO.h"
#include "../Config/GPIO_Cfg.h"
#include "../Mcal/Inc/TM4C123GH6PM_GPT.h"
#include "../Common/Mcu_Hw.h"
#include "../Config/IntCtrl_Cfg.h"
#include "../Mcal/Inc/IntCtrl.h"
#include "../Mcal/Inc/IntCtrl_Types.h"
#include "../Mcal/Inc/TM4c123GH6PM_SysTick.h"

extern Port_ConfigType PortConfig;
extern IntCtrl_ConfigType IntCtrlConfig;
extern GPT_ConfigType GPT_Config;
extern SysTick_ConfigType STConfig;

void LedOnPWM_Period (uint32 OnTime, uint32 OffTime );


int main(void)
{
	IntCtrl_Init(&IntCtrlConfig);
	GPT_init(&GPT_Config);
	port_init(&PortConfig);
	SysTick_init(&STConfig);

	while(1)
	{

		LedOnPWM_Period(1000 , 500);

	}
}



void LedOnPWM_Period (uint32 OnTime, uint32 OffTime )
{
	StartSysTick (OffTime);
	StartSysTick (OnTime);
}
