/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : usbd_cdc_if.c
 * @version        : v1.0_Cube
 * @brief          : Usb device for Virtual Com Port.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"
#include "cmsis_os.h"

/* USER CODE BEGIN INCLUDE */
#define FALSE 0
#define TRUE !FALSE
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */
#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */
static struct
{
	uint8_t Buffer[APP_RX_DATA_SIZE];
	int Position, Size;
	char ReadDone;
} RxBuffer;

USBD_HandleTypeDef *hUsbDevice_0 = 0;

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
  /* USER CODE BEGIN 3 */
	/* Set Application Buffers */
	hUsbDevice_0 = &hUsbDeviceFS;

	RxBuffer.Position = 0;		// reset read position
	RxBuffer.Size = 0;			// reset size
	RxBuffer.ReadDone = TRUE;// mark the read as done --- nothing can be read till we receive data

	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, RxBuffer.Buffer);
	USBD_CDC_ReceivePacket(hUsbDevice_0);

	return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  /* USER CODE BEGIN 4 */
	return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
	static uint8_t lineBuf[16];

  /* USER CODE BEGIN 5 */
	switch (cmd)
	{
		case CDC_SEND_ENCAPSULATED_COMMAND:

			break;

		case CDC_GET_ENCAPSULATED_RESPONSE:

			break;

		case CDC_SET_COMM_FEATURE:

			break;

		case CDC_GET_COMM_FEATURE:

			break;

		case CDC_CLEAR_COMM_FEATURE:

			break;

			/*******************************************************************************/
			/* Line Coding Structure                                                       */
			/*-----------------------------------------------------------------------------*/
			/* Offset | Field       | Size | Value  | Description                          */
			/* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
			/* 4      | bCharFormat |   1  | Number | Stop bits                            */
			/*                                        0 - 1 Stop bit                       */
			/*                                        1 - 1.5 Stop bits                    */
			/*                                        2 - 2 Stop bits                      */
			/* 5      | bParityType |  1   | Number | Parity                               */
			/*                                        0 - None                             */
			/*                                        1 - Odd                              */
			/*                                        2 - Even                             */
			/*                                        3 - Mark                             */
			/*                                        4 - Space                            */
			/* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
			/*******************************************************************************/
		case CDC_SET_LINE_CODING:
			if(length <= sizeof(lineBuf))
				memcpy(lineBuf, pbuf, length);		// save from pbuf to lineBuf
			break;

		case CDC_GET_LINE_CODING:
			if(length <= sizeof(lineBuf))
				memcpy(pbuf, lineBuf, length);		// lineBuf to pbuf

			break;

		case CDC_SET_CONTROL_LINE_STATE:

			break;

		case CDC_SEND_BREAK:

			break;

		default:
			break;
	}

	return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will block any OUT packet reception on USB endpoint
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result
  *         in receiving more data while previous ones are still not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  /* USER CODE BEGIN 6 */

	// got a new packet of data
	RxBuffer.Position = 0;		// reset read position
	RxBuffer.Size = *Len;			// save the size we just got
	RxBuffer.ReadDone = FALSE;		// mark the struct as not yet processed

	//  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
	//  USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  CDC_Transmit_FS
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 7 */
	USBD_CDC_HandleTypeDef *hcdc =
			(USBD_CDC_HandleTypeDef*) hUsbDeviceFS.pClassData;
	if (hcdc->TxState != 0)
	{
		return USBD_BUSY;
	}
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
	result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 7 */
  return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
int VCP_read(void *pBuffer, int size)
{
	if ((RxBuffer.ReadDone) || (RxBuffer.Size <= 0))		// no new data so return
		return 0;

	int remaining = RxBuffer.Size - RxBuffer.Position;
	int todo = MIN(remaining, size);// got data, process which ever is smaller, buffer size or remaining usb data
	if (todo <= 0)
		return 0;

	memcpy(pBuffer, RxBuffer.Buffer + RxBuffer.Position, todo);	// copy it over
	RxBuffer.Position += todo;
	if (RxBuffer.Position >= RxBuffer.Size)
	{
		RxBuffer.ReadDone = TRUE;					// all done, so mark as empty
		RxBuffer.Position = -1;
		RxBuffer.Size = -2;
		// tell the usb device we are ready for another pkt
		USBD_CDC_SetRxBuffer(&hUsbDeviceFS, RxBuffer.Buffer);
		USBD_CDC_ReceivePacket(hUsbDevice_0);
	}

	return todo;
}

int VCP_ReadLine(void *pBuffer, int size)	// read USB till I find \n or \r
{
	int count = 0;
	uint8_t bFound = 0;

	while((!bFound) && (size > 1))
	{
		if((RxBuffer.ReadDone) || (RxBuffer.Size <= 0))		// no new data	-- so yeild
			osThreadYield();

		int remaining = RxBuffer.Size - RxBuffer.Position;
		int todo = MIN(remaining, (size-1));// got data, process which ever is smaller, buffer size or remaining usb data

		memcpy(pBuffer, RxBuffer.Buffer + RxBuffer.Position, todo);	// copy it over
		count += todo;
		size -= todo;
		pBuffer += todo;
		for(int i = 0; i < RxBuffer.Size; i++)
		{
			char ch = RxBuffer.Buffer[RxBuffer.Position + i];
			if(ch == '\n' || ch == '\r')
			{
				break;
				bFound = 1;
			}
		}
		RxBuffer.Position += todo;
		if (RxBuffer.Position >= RxBuffer.Size)
		{
			RxBuffer.ReadDone = TRUE;					// all done, so mark as empty
			RxBuffer.Position = -1;
			RxBuffer.Size = -2;
			// tell the usb device we are ready for another pkt
			USBD_CDC_SetRxBuffer(&hUsbDeviceFS, RxBuffer.Buffer);
			USBD_CDC_ReceivePacket(hUsbDevice_0);
		}
	}
	return count;
}

int VCP_write(const void *pBuffer, int size)
{
	if (size > APP_TX_DATA_SIZE)
	{
		int offset;
		int done = 0;
		for (offset = 0; offset < size; offset += done)
		{
			int todo = MIN(APP_TX_DATA_SIZE, size - offset);
			done = VCP_write(((char*) pBuffer) + offset, todo);
			if (done != todo)
				return offset + done;
		}

		return size;
	}

	USBD_CDC_HandleTypeDef *pCDC =
			(USBD_CDC_HandleTypeDef*) hUsbDeviceFS.pClassData;

	if (pCDC != NULL)
	{
		while (pCDC->TxState)
		{
		} //Wait for previous transfer
	}

	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, (uint8_t*) pBuffer, size);
	if (USBD_CDC_TransmitPacket(&hUsbDeviceFS) != USBD_OK)
		return 0;

	if (pCDC != NULL)
		while (pCDC->TxState)
		{
		} //Wait until transfer is done

	return size;
}

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
