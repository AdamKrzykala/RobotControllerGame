/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2019 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "spi.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "stm32f429i_discovery_ts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
globalClass* globalClassHandler;
SPI_HandleTypeDef* p_hspi4;
uint8_t config_address = 0x20;
uint8_t config_data = 0x27;
uint8_t Address_ACCX = 0x29;
uint8_t Address_ACCY = 0x2B;
uint8_t Address_ACCZ = 0x2D;

TS_StateTypeDef struktura;
TS_StateTypeDef* ts_struct;
uint32_t initTime;
int flagTouch = 0; //1 - touch detected -> need do delete flag           0-touch not detected
/* USER CODE END Variables */
osThreadId mpuTaskHandle;
osThreadId lcdTaskHandle;
osThreadId touchTaskHandle;
osThreadId gameTaskHandle;
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartLCD_handling(void const * argument);
void StartTS_handling(void const * argument);
void StartMPU_handling(void const * argument);
void StartGAME_master(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	ts_struct = &struktura;
	ts_init(ts_struct);
	initMenu(ts_struct);
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
		/* definition and creation of mpuTask */
		osThreadDef(mpuTask, StartDefaultTask, osPriorityNormal, 0, 128);
		//empty thread

		/* definition and creation of lcdTask */
		osThreadDef(LCD_handling, StartLCD_handling, osPriorityNormal, 0, 128);
		lcdTaskHandle = osThreadCreate(osThread(LCD_handling), NULL);

		/* definition and creation of touchTask */
		osThreadDef(TS_handling, StartTS_handling, osPriorityNormal, 0, 128);
		touchTaskHandle = osThreadCreate(osThread(TS_handling), NULL);

		/* definition and creation of mpuTask */
		osThreadDef(MPU_handling, StartMPU_handling, osPriorityNormal, 0, 128);
		mpuTaskHandle = osThreadCreate(osThread(MPU_handling), NULL);

		/* definition and creation of mpuTask */
		osThreadDef(GAME_master, StartGAME_master, osPriorityNormal, 0, 128);
		gameTaskHandle = osThreadCreate(osThread(GAME_master), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the mpuTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument) {

	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
 * @brief Function implementing the lcdTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask02 */
void StartLCD_handling(void const * argument) {
	/* USER CODE BEGIN StartTask02 */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
		if (HAL_GetTick() - initTime >= 50) {
			flagTouch = 0; //wyzerowanie flagi

			Display(globalClassHandler);
			Service();
			initTime = HAL_GetTick(); //eliminacja drgan
		}

	}
	/* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
 * @brief Function implementing the touchTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask03 */
void StartTS_handling(void const * argument) {
	/* USER CODE BEGIN StartTask03 */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
		BSP_TS_GetState(ts_struct);
		if (ts_struct->TouchDetected) {
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		}
		else {
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
		}

		//sprawdz led

	}
	/* USER CODE END StartTask03 */
}

/* USER CODE END Header_StartDefaultTask */
void StartMPU_handling(void const * argument) {

	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	writegyro(hspi4, config_address, 0x0F);
	for (;;) {
		osDelay(1);
		globalClassHandler->gyroVarX = readgyro(hspi4, Address_ACCX, globalClassHandler->gyroVarX);
		globalClassHandler->gyroVarY = readgyro(hspi4, Address_ACCY, globalClassHandler->gyroVarY);
		globalClassHandler->gyroVarZ = readgyro(hspi4, Address_ACCZ, globalClassHandler->gyroVarZ);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE END Header_StartDefaultTask */
void StartGAME_master(void const * argument) {

	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
