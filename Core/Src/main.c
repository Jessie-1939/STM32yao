/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include "stm32f1xx_hal_gpio.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    LED_PIN_0 = GPIO_PIN_0,
    LED_PIN_1 = GPIO_PIN_1,
    LED_PIN_2 = GPIO_PIN_5,
    LED_PIN_3 = GPIO_PIN_6,
    LED_PIN_4 = GPIO_PIN_12,
    LED_PIN_5 = GPIO_PIN_13,
} LED_Pin;

typedef struct {
    LED_Pin pin;
    int status;
} LEDStatus;

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
LEDStatus led_status[6] = {
    {LED_PIN_0, 0},
    {LED_PIN_1, 0},
    {LED_PIN_2, 0},
    {LED_PIN_3, 0},
    {LED_PIN_4, 0},
    {LED_PIN_5, 0}
};

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void SetLEDStatusBasedOnNumbers(int numbers[6]);
void ControlLEDs(void);

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void SetLEDStatusBasedOnNumbers(int numbers[6]) {
    for (int i = 0; i < 6; ++i) {
        switch (numbers[i]) {
            case 6:
                led_status[i].status = 0;
                break;
            case 7:
                led_status[i].status = 1;
                break;
            case 8:
                led_status[i].status = 2;
                break;
            case 9:
                led_status[i].status = 3;
                break;
        }
    }
}

void ControlLEDs(void) {
    static uint32_t last_time = 0;
    uint32_t current_time = HAL_GetTick();
    
    //0和3都是闪烁，1是常亮，2是不亮，0号LED的闪烁周期为3秒（亮2秒，暗1秒），而3号LED的闪烁周期也是3秒（亮1秒，暗2秒）。
     for (int i = 0; i < 6; i++) {
        switch (led_status[i].status) {
            case 0:
                if ((current_time - last_time) % 6000 < 4000) { // 0号LED 亮2秒，暗1秒
                    HAL_GPIO_WritePin(GPIOB, led_status[i].pin, GPIO_PIN_SET);
                } else {
                    HAL_GPIO_WritePin(GPIOB, led_status[i].pin, GPIO_PIN_RESET);
                }
                break;
            case 1:
                HAL_GPIO_WritePin(GPIOB, led_status[i].pin, GPIO_PIN_SET); // 1号LED 常亮
                break;
            case 2:
                HAL_GPIO_WritePin(GPIOB, led_status[i].pin, GPIO_PIN_RESET); // 2号LED 不亮
                break;
            case 3:
                if ((current_time - last_time) % 6000 < 1000) { // 3号LED 亮1秒，暗2秒
                    HAL_GPIO_WritePin(GPIOB, led_status[i].pin, GPIO_PIN_SET);
                } else {
                    HAL_GPIO_WritePin(GPIOB, led_status[i].pin, GPIO_PIN_RESET);
                }
                break;
        }
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  int numbers[6] = {6, 7, 8, 9, 8, 9};
  SetLEDStatusBasedOnNumbers(numbers);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* Infinite loop */
  while (1)
  {
    ControlLEDs();
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB12 PB13 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
