/*
 * MainTask.c
 *
 *  Created on: Nov 15, 2019
 *      Author: archer
 */
#include <stdio.h>
#include <spdTasks.h>
#include "main.h"
#include "message.h"
#include "usbd_cdc_if.h"
#include "printf.h"
#include "jsmn.h"
#include "FSMCTool.h"

//
// global Task and message queues
//

osThreadId TaskMainHandle;
osThreadId TaskSocket1Handle;
osThreadId TaskSocket2Handle;
osThreadId TaskSocket3Handle;
osThreadId TaskSocket4Handle;

osMessageQId ResultsQHandle;
osMessageQId SocketQ1Handle;
osMessageQId SocketQ2Handle;
osMessageQId SocketQ3Handle;
osMessageQId SocketQ4Handle;

// Message Pool
osPoolId MsgPool;
osPoolDef(MsgPool, 32, T_MSG);

extern void MX_USB_DEVICE_Init(void);

//
//	Start the threads, create the message queue, setup the message pool
//
void StartThreads()
{
	// init USB
	MX_USB_DEVICE_Init();

	/* definition and creation of SocketQ1 */
	osMessageQDef(SocketQ1, 16, T_MSG);
	SocketQ1Handle = osMessageCreate(osMessageQ(SocketQ1), NULL);

	/* definition and creation of ResultsQ */
	osMessageQDef(ResultsQ, 16, T_MSG);
	ResultsQHandle = osMessageCreate(osMessageQ(ResultsQ), NULL);

	/* definition and creation of SocketQ2 */
	osMessageQDef(SocketQ2, 16, T_MSG);
	SocketQ2Handle = osMessageCreate(osMessageQ(SocketQ2), NULL);

	/* definition and creation of SocketQ3 */
	osMessageQDef(SocketQ3, 16, T_MSG);
	SocketQ3Handle = osMessageCreate(osMessageQ(SocketQ3), NULL);

	/* definition and creation of SocketQ4 */
	osMessageQDef(SocketQ4, 16, T_MSG);
	SocketQ4Handle = osMessageCreate(osMessageQ(SocketQ4), NULL);

	/* definition and creation of defaultTask */
	osThreadDef(TaskMain, StartTaskMain, osPriorityNormal, 0, 2048);
	TaskMainHandle = osThreadCreate(osThread(TaskMain), NULL);

	/* definition and creation of TaskSocket1 */
	osThreadDef(TaskSocket1, StartTaskSocket, osPriorityNormal, 0, 2048);
	TaskSocket1Handle = osThreadCreate(osThread(TaskSocket1), (void*) 1);

	/* definition and creation of TaskSocket2 */
	osThreadDef(TaskSocket2, StartTaskSocket, osPriorityNormal, 0, 2048);
	TaskSocket2Handle = osThreadCreate(osThread(TaskSocket2), (void*) 2);

	/* definition and creation of TaskSocket3 */
	osThreadDef(TaskSocket3, StartTaskSocket, osPriorityNormal, 0, 2048);
	TaskSocket3Handle = osThreadCreate(osThread(TaskSocket3), (void*) 3);

	/* definition and creation of TaskSocket4 */
	osThreadDef(TaskSocket4, StartTaskSocket, osPriorityNormal, 0, 2048);
	TaskSocket4Handle = osThreadCreate(osThread(TaskSocket4), (void*) 4);

	MsgPool = osPoolCreate(osPool(MsgPool));

}

osStatus SendMessage(uint8_t skt, T_MSG *pMsg)
{
	osStatus retVal = osErrorParameter;

	switch (skt)
	{
		case 1:
			// osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
			retVal = osMessagePut(SocketQ1Handle, (uint32_t) pMsg,
					osWaitForever);
			break;
		case 2:
			// osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
			retVal = osMessagePut(SocketQ2Handle, (uint32_t) pMsg,
					osWaitForever);
			break;
		case 3:
			// osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
			retVal = osMessagePut(SocketQ3Handle, (uint32_t) pMsg,
					osWaitForever);
			break;
		case 4:
			// osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
			retVal = osMessagePut(SocketQ4Handle, (uint32_t) pMsg,
					osWaitForever);
			break;
	}

	return retVal;
}

void ShowMenu()
{
	printf("\n\r\n\r");
	printf("\n\rDemo Menu 0.01 \n\r");

	for(int i = 1; i <= 4; i++)
		printf("\t%d:\tActivate Socket %d\n\r", i, i);;
	printf("\n R -- DFU Reboot\n\r");
	printf("\n F -- FSMC Tool\n\r");
}

/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartTaskMain(void const *argument)
{
	uint8_t activeSkt = 1;
	char buf[8];

	/* Infinite loop */
	for (;;)
	{
		//
		// Read the pin
		//

		if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET)
		{
			// if it is low

			VCP_write("MainTask\n\r", 10);

			// turn off all the LEDS
			HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD2_Pin,	GPIO_PIN_RESET);

			// get a message buffer from the pool
			T_MSG *pDisableMsg = osPoolAlloc(MsgPool);
			T_MSG *pEnableMsg = osPoolAlloc(MsgPool);

			// send disable message -- to active socket
			pDisableMsg->msgType = spdDISABLE;
			SendMessage(activeSkt, pDisableMsg);

			// advance to next socket -- wrap if needed
			activeSkt += 1;
			if (activeSkt > 4)
				activeSkt = 1;

			// send enable message -- to next socket
			pEnableMsg->msgType = spdENABLE;
			SendMessage(activeSkt, pEnableMsg);

			// wait for the pin to go back
			while (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin)
					== GPIO_PIN_SET)
				osDelay(100);
		}
		if(VCP_read(buf, 1) == 1)
		{
			T_MSG *pDisableMsg = osPoolAlloc(MsgPool);
			T_MSG *pEnableMsg = osPoolAlloc(MsgPool);

			// disable the current socket
			if((buf[0] >= '1') && (buf[0] <= '4'))
			{
				pDisableMsg->msgType = spdDISABLE;
				SendMessage(activeSkt, pDisableMsg);
				activeSkt = buf[0] - '0';
				// send enable message -- to user socket
				pEnableMsg->msgType = spdENABLE;
				SendMessage(activeSkt, pEnableMsg);
			}
			else if(buf[0] == 'R')
			{
				osPoolFree(MsgPool, pDisableMsg);		// not going to send msg so be sure to free it
				osPoolFree(MsgPool, pEnableMsg);
				dfu_run_bootloader();
			}
			else if(buf[0] == 'F')
			{
				osPoolFree(MsgPool, pDisableMsg);		// not going to send msg so be sure to free it
				osPoolFree(MsgPool, pEnableMsg);
				FSMCTool();

			}
			else
			{
				osPoolFree(MsgPool, pDisableMsg);		// not going to send msg so be sure to free it
				osPoolFree(MsgPool, pEnableMsg);
				ShowMenu();
			}

		}
		osThreadYield();
	}
	/* USER CODE END 5 */
}
