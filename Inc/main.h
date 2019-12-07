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
#include "stm32f0xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_INB_Pin GPIO_PIN_13
#define B1_INB_GPIO_Port GPIOC
#define B1_DIAGB_Pin GPIO_PIN_14
#define B1_DIAGB_GPIO_Port GPIOC
#define SHARP_L1_Pin GPIO_PIN_0
#define SHARP_L1_GPIO_Port GPIOF
#define SHARP_L2_Pin GPIO_PIN_1
#define SHARP_L2_GPIO_Port GPIOF
#define B1_CS_Pin GPIO_PIN_0
#define B1_CS_GPIO_Port GPIOA
#define KTIR_L1_Pin GPIO_PIN_1
#define KTIR_L1_GPIO_Port GPIOA
#define KTIR_L2_Pin GPIO_PIN_2
#define KTIR_L2_GPIO_Port GPIOA
#define KTIR_R1_Pin GPIO_PIN_3
#define KTIR_R1_GPIO_Port GPIOA
#define KTIR_R2_Pin GPIO_PIN_4
#define KTIR_R2_GPIO_Port GPIOA
#define BAT_VCC_Pin GPIO_PIN_5
#define BAT_VCC_GPIO_Port GPIOA
#define B2_CS_Pin GPIO_PIN_6
#define B2_CS_GPIO_Port GPIOA
#define B2_INA_Pin GPIO_PIN_7
#define B2_INA_GPIO_Port GPIOA
#define SHARP_R1_Pin GPIO_PIN_0
#define SHARP_R1_GPIO_Port GPIOB
#define SHARP_R2_Pin GPIO_PIN_1
#define SHARP_R2_GPIO_Port GPIOB
#define B2_DIAGA_Pin GPIO_PIN_2
#define B2_DIAGA_GPIO_Port GPIOB
#define B2_INB_Pin GPIO_PIN_12
#define B2_INB_GPIO_Port GPIOB
#define B2_DIAGB_Pin GPIO_PIN_13
#define B2_DIAGB_GPIO_Port GPIOB
#define SW_START_Pin GPIO_PIN_15
#define SW_START_GPIO_Port GPIOB
#define B1_DIAGA_Pin GPIO_PIN_11
#define B1_DIAGA_GPIO_Port GPIOF
#define B1_INA_Pin GPIO_PIN_8
#define B1_INA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
