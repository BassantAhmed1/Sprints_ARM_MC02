/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"

#include "queue.h"
#include "string.h"


/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )
	
extern unsigned char txBuffer[200];

TaskHandle_t * Load1Simulation_Handler = NULL;
TaskHandle_t * Load2Simulation_Handler = NULL;

uint8_t RisingFlag1 =0;
uint8_t FallingFlag1 =0;

uint8_t RisingFlag2 =0;
uint8_t FallingFlag2 =0;

/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/

/*Using Queue*/
unsigned char Button1_Rising_Monitor [20];
unsigned char Button1_Falling_Monitor [20];
unsigned char Button2_Rising_Monitor [20];
unsigned char Button2_Falling_Monitor [20];
unsigned char Periodic_Tx [20];

TaskHandle_t * Button1_Handler = NULL;
TaskHandle_t * Button2_Handler = NULL;
TaskHandle_t * PeriodicTx_Handler = NULL;
TaskHandle_t * UartRx_Handler = NULL;


QueueHandle_t xQueue1 ,xQueue2,xQueue3;

void Button_1_Monitor( void * pvParameters )
{
	//giving the task an ID tag = 1
	vTaskSetApplicationTaskTag( NULL, ( void * ) 1 );
	
	uint8_t now , last;
	
	TickType_t xLastWakeTime;
		const TickType_t xFrequency = 50;
		
		// Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Task code goes here. */
		now = GPIO_read(PORT_0 , PIN0);
		
		
		//detect rising and falling edges
		if (now != last) {
				if (now > 0)  //rising edge
				{
					RisingFlag1=1;
					strcpy((char *)&Button1_Rising_Monitor, "\nRising edge1");
					xQueueSend( xQueue1 ,( void * ) &Button1_Rising_Monitor ,0);
				}
					
				else if (now == 0)		//falling edge
				{
					FallingFlag1 = 1;
					strcpy((char *)&Button1_Falling_Monitor, "\nFalling edge1");
					xQueueSend( xQueue1 ,( void * ) &Button1_Falling_Monitor,0);
				
				}
					
				last = now;
				RisingFlag1=0;
				FallingFlag1=0;
		}
		
		

		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void Button_2_Monitor( void * pvParameters )
{
	//giving the task an ID tag = 2
	vTaskSetApplicationTaskTag( NULL, ( void * ) 2 );
	
	uint8_t now , last;
	
	
	TickType_t xLastWakeTime;
		const TickType_t xFrequency = 50;
		
		// Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Task code goes here. */
		now = GPIO_read(PORT_0 , PIN1);
		
		RisingFlag2=0;
		FallingFlag2=0;
		//detect rising and falling edges
		if (now != last) {
				if (now > 0)  //rising edge
				{
					RisingFlag2=1;
					strcpy((char *)&Button2_Rising_Monitor, "\nRising edge2");
					xQueueSend( xQueue2 ,( void * ) &Button2_Rising_Monitor ,0);
				}
					
				else if (now == 0)		//falling edge
				{
					FallingFlag2 = 1;
					strcpy((char *)&Button2_Falling_Monitor, "\nFalling edge2");
					xQueueSend( xQueue2 ,( void * ) &Button2_Falling_Monitor ,0 );
				
				}
					
				last = now;
		}

		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}


void Periodic_Transmitter( void * pvParameters )
{
	//giving the task an ID tag = 3
	vTaskSetApplicationTaskTag( NULL, ( void * ) 3 );
	
		TickType_t xLastWakeTime;
		const TickType_t xFrequency = 100;
		
		// Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();
	strcpy((char *)&Periodic_Tx, "\nperiod ");
	for( ;; )
	{
		/* Task code goes here. */
			 
		xQueueSend( xQueue3 ,( void * ) &Periodic_Tx , 0);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void Uart_Receiver( void * pvParameters )
{
	//giving the task an ID tag = 4
	vTaskSetApplicationTaskTag( NULL, ( void * ) 4 );
	
	char string [20];
	
		TickType_t xLastWakeTime;
		const TickType_t xFrequency = 20;
		
		// Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Task code goes here. */
		//ButtonState = GPIO_read(PORT_0 , PIN0);
		
		//sending Button_1_monitor data
		while (xQueueReceive(xQueue1, string, (TickType_t) 0))
		{
		vSerialPutString((signed char *) string, (unsigned short) 20);
		xSerialPutChar('\n');
		}
		
		//sending Button_2_monitor data
		while (xQueueReceive(xQueue2, string, (TickType_t) 0))
		{
		vSerialPutString((signed char *) string, (unsigned short) 20);
		xSerialPutChar('\n');
		}
		
		//sending Periodic_Tx data
		while (xQueueReceive(xQueue3, string, (TickType_t) 0))
		{
		vSerialPutString((signed char *) string, (unsigned short) 20);
		xSerialPutChar('\n');
		}

		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}


void vApplicationTickHook (void)
{
	GPIO_write(PORT_0, PIN2 , PIN_IS_HIGH);
	GPIO_write(PORT_0, PIN2 , PIN_IS_LOW);
	//write your code here
}

void Load_1_Simulation ( void * pvParameters )
{
	//giving the task an ID tag = 5
	vTaskSetApplicationTaskTag( NULL, ( void * ) 5 );
	
	TickType_t xLastWakeTime = xTaskGetTickCount();
	uint32_t i = 0;
	for( ; ; )
	{
 		for( i = 0 ; i <= 37000; i++);		//5ms period
		/*Periodicity: 10*/
		vTaskDelayUntil( &xLastWakeTime ,(TickType_t) 10);

	}
}

void Load_2_Simulation ( void * pvParameters )
{
	//giving the task an ID tag = 6
	vTaskSetApplicationTaskTag( NULL, ( void * ) 6 );
	
	TickType_t xLastWakeTime = xTaskGetTickCount();
	uint32_t i = 0;		
	for( ; ; )
	{		
		for( i = 0 ; i <= 88800; i++);		//12ms period
		/*Periodicity: 100*/
		vTaskDelayUntil( &xLastWakeTime , (TickType_t)100);	
	}
}

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
	xSerialPortInitMinimal( mainCOM_TEST_BAUD_RATE);
	xQueue1 = xQueueCreate( 20, sizeof( char[20] ) );
	xQueue2 = xQueueCreate( 20, sizeof( char[20] ) );
	xQueue3 = xQueueCreate( 20, sizeof( char[20] ) );

    /* Create Tasks here */
xTaskPeriodicCreate(
			Button_1_Monitor,			/* Function that implements the task. */
			"Button_1_Monitor",			/* Text name for the task. */
			50,					/* Stack size in words, not bytes. */
			NULL,			/* Parameter passed into the task. */
			1,						/* Priority at which the task is created. */
			Button1_Handler,/* Used to pass out the created task's handle. */
			50);		
	
	xTaskPeriodicCreate(
			Button_2_Monitor,			/* Function that implements the task. */
			"Button_1_Monitor",			/* Text name for the task. */
			50,					/* Stack size in words, not bytes. */
			NULL,			/* Parameter passed into the task. */
			1,						/* Priority at which the task is created. */
			Button2_Handler,/* Used to pass out the created task's handle. */
			50);		

	xTaskPeriodicCreate(
			Periodic_Transmitter,			/* Function that implements the task. */
			"Periodic_Tx",			/* Text name for the task. */
			50,					/* Stack size in words, not bytes. */
			NULL,			/* Parameter passed into the task. */
			1,						/* Priority at which the task is created. */
			PeriodicTx_Handler,/* Used to pass out the created task's handle. */
			100);		
			
	xTaskPeriodicCreate(
			Uart_Receiver,			/* Function that implements the task. */
			"Uart_Receiver",			/* Text name for the task. */
			100,					/* Stack size in words, not bytes. */
			NULL,			/* Parameter passed into the task. */
			1,						/* Priority at which the task is created. */
			UartRx_Handler,/* Used to pass out the created task's handle. */
			20);		


xTaskPeriodicCreate(
			Load_1_Simulation,                 /* Function that implements the task. */
			"LOAD 1 SIMULATION",               /* Text name for the task. */
			100,                               /* Stack size in words, not bytes. */
			( void * ) 0,                      /* Parameter passed into the task. */
			1,                                 /* Priority at which the task is created. */
			Load1Simulation_Handler,      /* Used to pass out the created task's handle. */
			10);	   /* Period for the task */

	xTaskPeriodicCreate(
			Load_2_Simulation,                 /* Function that implements the task. */
			"LOAD 1 SIMULATION",               /* Text name for the task. */
			100,                               /* Stack size in words, not bytes. */
			( void * ) 0,                      /* Parameter passed into the task. */
			1,                                 /* Priority at which the task is created. */
			Load2Simulation_Handler,      /* Used to pass out the created task's handle. */
			100); 	 /* Period for the task */

	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/


