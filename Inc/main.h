/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define IR1_Pin GPIO_PIN_0
#define IR1_GPIO_Port GPIOC
#define IR2_Pin GPIO_PIN_1
#define IR2_GPIO_Port GPIOC
#define IR3_Pin GPIO_PIN_2
#define IR3_GPIO_Port GPIOC
#define IR4_Pin GPIO_PIN_3
#define IR4_GPIO_Port GPIOC
#define IR55_Pin GPIO_PIN_4
#define IR55_GPIO_Port GPIOC
#define R1_Pin GPIO_PIN_12
#define R1_GPIO_Port GPIOB
#define R2_Pin GPIO_PIN_13
#define R2_GPIO_Port GPIOB
#define R3_Pin GPIO_PIN_14
#define R3_GPIO_Port GPIOB
#define R4_Pin GPIO_PIN_15
#define R4_GPIO_Port GPIOB
#define L1_Pin GPIO_PIN_6
#define L1_GPIO_Port GPIOC
#define L2_Pin GPIO_PIN_7
#define L2_GPIO_Port GPIOC
#define L3_Pin GPIO_PIN_8
#define L3_GPIO_Port GPIOC
#define L4_Pin GPIO_PIN_9
#define L4_GPIO_Port GPIOC
#define KEY_Pin GPIO_PIN_11
#define KEY_GPIO_Port GPIOA
#define IR5_Pin GPIO_PIN_12
#define IR5_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOD
#define A0_Pin GPIO_PIN_3
#define A0_GPIO_Port GPIOB
#define A1_Pin GPIO_PIN_4
#define A1_GPIO_Port GPIOB
#define A2_Pin GPIO_PIN_5
#define A2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
typedef struct {
    char x; //坐标x
    char y; //坐标y
    char dir; //绝对方向
}carInfoType;
#define DPI 17
#define LEN 64
#define DPI 17
#define ENDX 1
#define ENDY 2
#define HIGHDPI 10
#define STKDEEP 200

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
