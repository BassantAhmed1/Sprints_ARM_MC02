/*
 * main.c
 *
 *  Created on: Aug 18, 2022
 *      Author: Bassant Ahmed
 */


#include "../Mcal/Inc/TM4C123GH6PM_GPIO.h"
#include "../Mcal/Inc/TM4C123GH6PM_GPT.h"
#include "../Common/Mcu_Hw.h"
#include "../Config/IntCtrl_Cfg.h"
#include "../Mcal/Inc/IntCtrl.h"
#include "../Mcal/Inc/IntCtrl_Types.h"

extern IntCtrl_ConfigType IntCtrlConfig;
//void Clk_Enable (void){
//	//Enable main oscillator
//	RCC->B.SYSDIV = 0x0;
//}
void LedOnPWM_Period (uint32 OnTime, uint32 OffTime ,  Dio_ChannelType PortChannelID);


int main(void)
{
	//Clk_Enable ();
	IntCtrl_Init(&IntCtrlConfig);
	GPIO_init();
	GPT_SetConfig_init();
	while(1)
	{

		LedOnPWM_Period(1000 , 1000 , Dio_PortF_PF1);

	}
}

void GPT_SetConfig_init (void)
{
	GPT_ConfigType GPTConfig;
	GPTConfig.ChannelID = WT0CCP0_PortC_PC4;
	GPTConfig.ChannelMode = GPT_ChannelMode_OneShot;
	GPTConfig.GPTChannelTickFreq = GPT_Freq_Define;
	GPTConfig.GPTChannelTickMax = 4000000;
	GPTConfig.GPTTimerType = Timer0_32_;

	GPT_init(&GPTConfig);

}

void GPIO_init(void){
	Port_ConfigType PortConfig;
	PortConfig.PortPinType =Dio_PortF_PF1;
	PortConfig.PortPinDirection = Port_PinDir_Output;
	PortConfig.PortPinMode = Port_PinMode_GPIO;
	PortConfig.PortPinOutputCurrent = Port_PinOutCurrent_4mA;

	port_init(&PortConfig);

}

void LedOnPWM_Period (uint32 OnTime, uint32 OffTime , Dio_ChannelType PortChannelID)
{
	GPT_StartTimer_0(OnTime);
	//toggle in interrupt
	Dio_WriteChannel(PortChannelID ,High );

	GPT_StartTimer_0(OffTime);
	Dio_WriteChannel(PortChannelID ,Low );

	//toggle in interrupt
}
