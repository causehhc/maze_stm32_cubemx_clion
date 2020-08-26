/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "User/maze.h"
#include "User/motor.h"
#include "User/infrared.h"

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

/* USER CODE BEGIN PV */
motorInfoType leftInfo;
motorInfoType rightInfo;
uint8_t maze[DPI][DPI] = {0x00};//走过是1，能走是1

char dirStack[100];
int dirStackIdx = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void para_init(carInfoType *carInfo, char x, char y, char dir){
  leftInfo.ENC = 0;
  leftInfo.PWM = 0;
  leftInfo.ADD = 0;
  leftInfo.TGT = 0;

  rightInfo.ENC = 0;
  rightInfo.PWM = 0;
  rightInfo.ADD = 0;
  rightInfo.TGT = 0;

  carInfo->x = x;
  carInfo->y = y;
  carInfo->dir = dir;

  maze[x][y] = 0x11;
}
char abs_to_rel(char nowDir, char absDir){
  return (nowDir+absDir)%4;
}
char read_map_wall(carInfoType carInfo, char dir){

}
char read_map_path(carInfoType carInfo, char dir){

}
void write_map_wall(carInfoType carInfo, char dir, char val){

}
void write_map_path(carInfoType carInfo, char dir, char val){

}
char isWall(carInfoType carInfo, char dir){
  char relDir = abs_to_rel(carInfo.dir, dir);
  char ir = read_IR(relDir);
  write_map_wall(carInfo, dir, ir);
  return ir;
}
char isNew(carInfoType carInfo, char dir){
  return read_map_path(carInfo, dir);
}
char search_dir(carInfoType carInfo){
  char aimDir = 0;
  for(int dir=1; dir<5; dir++){
    aimDir = isWall(carInfo, dir);
    if(isNew(carInfo, aimDir)){
      return aimDir;
    }
  }
  return aimDir;
}
void go_to_next(carInfoType carInfo, char nextDir){
  char relDir = abs_to_rel(carInfo.dir, nextDir);
  if(relDir == 1) {
    go_straight(&leftInfo, &rightInfo, 999);
  }
  if(relDir == 2) {
    go_left(&leftInfo, &rightInfo, 999);
  }
  if(relDir == 3) {
    go_right(&leftInfo, &rightInfo, 999);
  }
  if(relDir == 4) {
    go_turn(&leftInfo, &rightInfo, 999);
  }
}
void flash_carInfo(carInfoType *carInfo, char nextDir){
  if(nextDir == 1){
    carInfo->x++;
  }
  if(nextDir == 2){
    carInfo->y--;
  }
  if(nextDir == 3){
    carInfo->x--;
  }
  if(nextDir == 4){
    carInfo->y++;
  }
  carInfo->dir = nextDir;
}
void flash_mapInfo(char x, char y){
  maze[x][y] |= 0x10;
}
void flash_pathStack(char dir){
  dirStack[dirStackIdx++] = dir;
}
char backtrack(){
  char backDir = 0;
  if(--dirStackIdx != -1){
    backDir = dirStack[dirStackIdx];
    if(backDir > 0) backDir += 2;
    if(backDir > 4) backDir -= 4;
  }
  return backDir;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  carInfoType carInfo; //小车自身信息
  char sprintFlag = 0;  //冲刺标记
  char nextDir = 0; //下一步绝对方向

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  para_init(&carInfo, 1, 1, 1);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1|TIM_CHANNEL_2);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1|TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
  HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if(sprintFlag == 0){  //探索阶段
      nextDir = search_dir(carInfo); //根据是否有墙和是否走过得出下一步的方向
    }else if(sprintFlag == 1){  //冲刺阶段
      nextDir = bestPath(); //根据计算得出的最优路径得出下一步的方向
    }

    if(nextDir == 0){ //如果无法得出下一步方向，进行回溯
      nextDir = backtrack();
      if(nextDir == 0){ //如果回溯栈空，说明以遍历回起点，准备冲刺
        creatBestPath();  //计算最优路径
        sprintFlag = 1; //切换冲刺标记
      }
    }

    go_to_next(carInfo, nextDir);  //执行
    flash_carInfo(&carInfo, nextDir); //刷新小车自身信息
    flash_mapInfo(carInfo.x, carInfo.y); //刷新地图信息
    flash_pathStack(carInfo.dir); //刷新方向栈
  }
}
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if (htim->Instance == htim6.Instance){ //10ms
    //motorControl
    check_ENC(&leftInfo, &rightInfo);
    plus_ADD(&leftInfo, &rightInfo);
    incremental_PI_A(&leftInfo);
    incremental_PI_B(&rightInfo);
    range_PWM(&leftInfo, &rightInfo, 6000);
    set_PWM(&leftInfo, &rightInfo);
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
