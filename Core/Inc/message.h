/**
  ******************************************************************************
  * @file           : message.h
  * @brief          : Header for messages passed around
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MESSAGE_H
#define __MESSAGE_H
#include "main.h"
#include "cmsis_os.h"

#define FALSE 0
#define TRUE !FALSE
#define BOOL uint8_t
//
// message types
//

typedef enum {
	spdENABLE = 1,
	spdDISABLE,
	spdDATA,
	spdPROGRAM,
	spdVERIFY,
	spdERASE,
	spdPASSED,
	spdFAILED
} eMessage	;

//
// Message Structure
//

typedef struct {
	eMessage 	msgType;
	uint32_t	count;			// number of data bytes in ptr (usually 0)
	uint8_t 	*ptr;			// can be null (usually will be null)
} T_MSG;

//
// external message pool
//

extern osPoolId  MsgPool;

#endif 		// __MESSAGE_H
