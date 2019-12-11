/*
 * SocketTask.c
 *
 *  Created on: Nov 15, 2019
 *      Author: archer
 *
 *      This file has the routines for socket SPD.
 *
 */
#include <spdTasks.h>
#include "main.h"
#include "message.h"
#include "printf.h"

/**
 * @brief Function implementing the Socket  thread.
 * @param argument: socket number
 *
 * @retval None
 */
/* USER CODE END Header_StartTaskSocket */

void StartTaskSocket(void const *argument)
{
	/* USER CODE BEGIN StartTaskSocket */
	int socket = (int) argument;
	BOOL active = FALSE;

	osMessageQId inputQ;

	// by default the 1st task is active
	if (socket == 1)
		active = TRUE;

	switch (socket)
	{
		case 1:
			inputQ = SocketQ1Handle;
			break;
		case 2:
			inputQ = SocketQ2Handle;
			break;
		case 3:
			inputQ = SocketQ3Handle;
			break;
		case 4:
			inputQ = SocketQ4Handle;
			break;
	}
	/* Infinite loop */
	for (;;)
	{
		// check the message q
		osEvent evt = osMessageGet(inputQ, 50);

		// if I have a message
		if (evt.status == osEventMessage)
		{
			T_MSG *pMsg = (T_MSG *)evt.value.p;

			// look at the type and figure what to do
			if (pMsg->msgType == spdENABLE)
				active = TRUE;
			if (pMsg->msgType == spdDISABLE)
				active = FALSE;

			printf("SocketTask %d, active=%d, pMsg=0x%x\n\r", socket, active, (unsigned int)pMsg);

			HAL_GPIO_WritePin(LD2_GPIO_Port, LD1_Pin | LD2_Pin, GPIO_PIN_RESET);

			// free the message
			osPoolFree(MsgPool, pMsg);
		}

		if (active)
		{
			uint32_t pin;
			if(socket == 0)	pin = 0;
			else if(socket == 1) pin = LD1_Pin;
			else if(socket == 2) pin = LD2_Pin;
			else if(socket == 3) pin = LD1_Pin | LD2_Pin;
			else if(socket == 4) pin = LD2_Pin | LD1_Pin;

			if(socket != 4)
			{
				HAL_GPIO_TogglePin(LD2_GPIO_Port, pin);
				osDelay(500);
			}
			else
				HAL_GPIO_WritePin(LD2_GPIO_Port, pin, GPIO_PIN_SET);
		}
		osThreadYield();	// let this task go to sleep
	}
	/* USER CODE END StartTaskSocket */
}

