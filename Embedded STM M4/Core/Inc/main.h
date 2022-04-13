/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "Device.h"
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TEST_PIN_Pin GPIO_PIN_9
#define TEST_PIN_GPIO_Port GPIOE
#define VFD_RS_Pin GPIO_PIN_15
#define VFD_RS_GPIO_Port GPIOB
#define VFD_CE_Pin GPIO_PIN_9
#define VFD_CE_GPIO_Port GPIOD
#define VFD_CLK_Pin GPIO_PIN_10
#define VFD_CLK_GPIO_Port GPIOD
#define SW_Left_Pin GPIO_PIN_11
#define SW_Left_GPIO_Port GPIOD
#define VFD_RESET_Pin GPIO_PIN_12
#define VFD_RESET_GPIO_Port GPIOD
#define SW_Down_Pin GPIO_PIN_14
#define SW_Down_GPIO_Port GPIOD
#define SW_Right_Pin GPIO_PIN_15
#define SW_Right_GPIO_Port GPIOD
#define DC_DIR_Pin GPIO_PIN_8
#define DC_DIR_GPIO_Port GPIOC
#define MOTOR_PWM_TIM1_Pin GPIO_PIN_8
#define MOTOR_PWM_TIM1_GPIO_Port GPIOA
#define SW_Decrease_Pin GPIO_PIN_11
#define SW_Decrease_GPIO_Port GPIOA
#define SW_Increase_Pin GPIO_PIN_12
#define SW_Increase_GPIO_Port GPIOA
#define ENCODER1_Pin GPIO_PIN_15
#define ENCODER1_GPIO_Port GPIOA
#define U_Sonic_CH1_O_Pin GPIO_PIN_10
#define U_Sonic_CH1_O_GPIO_Port GPIOC
#define U_Sonic_CH1_I_Pin GPIO_PIN_11
#define U_Sonic_CH1_I_GPIO_Port GPIOC
#define ENCODER2_Pin GPIO_PIN_3
#define ENCODER2_GPIO_Port GPIOB
#define Servo_Pin GPIO_PIN_8
#define Servo_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

extern ADC_HandleTypeDef hadc1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim10;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
