/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void __initialize_hardware_early(void);
void dfu_run_bootloader(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define PMUX0_Pin GPIO_PIN_6
#define PMUX0_GPIO_Port GPIOF
#define PMUX1_Pin GPIO_PIN_7
#define PMUX1_GPIO_Port GPIOF
#define PMUX2_Pin GPIO_PIN_8
#define PMUX2_GPIO_Port GPIOF
#define PMUX3_Pin GPIO_PIN_9
#define PMUX3_GPIO_Port GPIOF
#define PMUX4_Pin GPIO_PIN_10
#define PMUX4_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ENA_12V3_Pin GPIO_PIN_0
#define ENA_12V3_GPIO_Port GPIOD
#define ENA_12V2_Pin GPIO_PIN_3
#define ENA_12V2_GPIO_Port GPIOD
#define ENA_12V1_Pin GPIO_PIN_4
#define ENA_12V1_GPIO_Port GPIOD
#define ENA_12V0_Pin GPIO_PIN_5
#define ENA_12V0_GPIO_Port GPIOD
#define ENA_I2C0_Pin GPIO_PIN_11
#define ENA_I2C0_GPIO_Port GPIOG
#define ENA_I2C1_Pin GPIO_PIN_12
#define ENA_I2C1_GPIO_Port GPIOG
#define ENA_I2C2_Pin GPIO_PIN_13
#define ENA_I2C2_GPIO_Port GPIOG
#define ENA_I2C3_Pin GPIO_PIN_14
#define ENA_I2C3_GPIO_Port GPIOG
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define PMUX_WE_Pin GPIO_PIN_8
#define PMUX_WE_GPIO_Port GPIOB
#define PMUX_CS_Pin GPIO_PIN_0
#define PMUX_CS_GPIO_Port GPIOE
#define PMUX_OE_Pin GPIO_PIN_1
#define PMUX_OE_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
