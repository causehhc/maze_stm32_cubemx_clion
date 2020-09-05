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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "User/maze.h"
#include "User/stepMotor.h"
#include "User/infrared.h"
#include "User/oled.h"

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
uint8_t RxBuffer1; //串口接收1
uint8_t RxBuffer2; //串口接收2

uint8_t maze[DPI][DPI] = {0x11};//新路�??????????1，有墙是1

char dirStack[STKDEEP] = {-1};
int dirStackIdx = 0;

extern char irR1, irR2, irR3, irR4, irR5;

char debug = 1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void para_init(carInfoType *carInfo, char x, char y, char dir){

  carInfo->x = x;
  carInfo->y = y;
  carInfo->dir = dir;

  init_maze(maze);
  init_stack(dirStack);

  maze[x][y] = 0x00;
}

/** 绝对方向�??????????       相对方向�??????????
  *     0           0：直�??????????
  * 3       1       1：右�??????????
  *     2           2：掉�??????????
  *                 3：左�??????????
**/
char banEdge(carInfoType carInfo, char absDir){
  if(carInfo.y!=1 || absDir!=0){
    if(carInfo.y!=15 || absDir!=2){
      if(carInfo.x!=1 || absDir!=3){
        if(carInfo.x!=15 || absDir!=1){
          return 1;
        }
      }
    }
  }
  return 0;
}
/* 判断此方向是否有�??????????*/
char isWall(carInfoType carInfo, char absDir){
  char relDir = abs_to_rel(carInfo.dir, absDir);
  char ir = read_DirIr(relDir);
  if(ir == -1){
    ir = read_map_wall(maze, carInfo, absDir);
  }else{
    if(banEdge(carInfo, absDir)){
      write_map_wall(maze, carInfo, absDir, ir);
    }else{
      ir = 1;
    }
  }
  return ir;
}

/* 判断此方向是否是新路*/
char isNew(carInfoType carInfo, char absDir){
  return read_map_path(maze, carInfo, absDir);
}

/* 搜索可走的所有方�??????????*/
char search_dir(carInfoType carInfo){
  char aimDir = -1;
  for(int absDir=0; absDir < 4; absDir++){
    isWall(carInfo, absDir);
  }
  for(int absDir=0; absDir < 4; absDir++){
    if(!isWall(carInfo, absDir)){
      if(isNew(carInfo, absDir)){
        aimDir = absDir;
        return aimDir;
      }
    }
  }
  return aimDir;
}

/* 前往相邻的下�??????????个方�??????????*/
void go_to_next(carInfoType carInfo, char nextDir){
  if(nextDir==255)  {
    return;
  }
  char relDir = abs_to_rel(carInfo.dir, nextDir);
  if(relDir == 0) {
    go_straight(104);
  }else if(relDir == 1) {
    go_right(48);
    go_straight(104);
  }else if(relDir == 2) {
    go_turn(96);
    go_straight(104);
  }else if(relDir == 3) {
    go_left(48);
    go_straight(104);
  }else{
  }
}

/* 刷新地图路径信息*/
void flash_mapPathInfo(carInfoType carInfo, char nextDir){
  write_map_path(maze, carInfo, nextDir, 0);
}

/* 刷新方向�??????????*/
void flash_pathStack(char dir){
  dirStack[dirStackIdx++] = dir;
}

/* 刷新小车自身信息*/
void flash_carInfo(carInfoType *carInfo, char nextDir){
  if(nextDir == 0)  carInfo->y-=2;
  if(nextDir == 1)  carInfo->x+=2;
  if(nextDir == 2)  carInfo->y+=2;
  if(nextDir == 3)  carInfo->x-=2;
  if(nextDir != 255 ) carInfo->dir = nextDir;
}

void flash_OLED_maze(){
  static char val;
  for(char x=0; x<DPI; x++) {
    for (char y = 0; y < DPI; y++) {
      if(maze[x][y] & 0x01) val = 1;
      else  val = 0;
      for (char i = 0; i < LEN / DPI; i++) {
        for (char j = 0; j < LEN / DPI; j++) {
          OLED_writeDPI(i + x * (LEN / DPI), j + y * (LEN / DPI), val);
        }
      }
    }
  }
}

void flash_OLED_carPos(carInfoType carInfo){
  for (char i = 0; i < (LEN / DPI)/2; i++) {
    for (char j = 0; j < (LEN / DPI)/2; j++) {
      OLED_writeDPI(i + carInfo.x*(LEN / DPI)+1, j + carInfo.y*(LEN / DPI)+1, 1);
    }
  }
  if(carInfo.dir == 0){
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1, carInfo.y*(LEN / DPI)+1-1, 1);
  }else if(carInfo.dir == 1){
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1+1, carInfo.y*(LEN / DPI)+1, 1);
  }else if(carInfo.dir == 2){
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1, carInfo.y*(LEN / DPI)+1+1, 1);
  }else{
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1-1, carInfo.y*(LEN / DPI)+1, 1);
  }
}

void flash_OLED_ir(){
  static char x=70,y=5;
  if(irR1){
    OLED_writeDPI(x, y-1, 1);
    OLED_writeDPI(x, y-2, 1);
    OLED_writeDPI(x, y-3, 1);
  }else{
    OLED_writeDPI(x, y-1, 0);
    OLED_writeDPI(x, y-2, 0);
    OLED_writeDPI(x, y-3, 0);
  }

  if(irR2){
    OLED_writeDPI(x-1, y-1, 1);
    OLED_writeDPI(x-2, y-2, 1);
    OLED_writeDPI(x-3, y-3, 1);
  }else{
    OLED_writeDPI(x-1, y-1, 0);
    OLED_writeDPI(x-2, y-2, 0);
    OLED_writeDPI(x-3, y-3, 0);
  }

  if(irR3){
    OLED_writeDPI(x-1, y, 1);
    OLED_writeDPI(x-2, y, 1);
    OLED_writeDPI(x-3, y, 1);
  }else{
    OLED_writeDPI(x-1, y, 0);
    OLED_writeDPI(x-2, y, 0);
    OLED_writeDPI(x-3, y, 0);
  }

  if(irR4){
    OLED_writeDPI(x+1, y-1, 1);
    OLED_writeDPI(x+2, y-2, 1);
    OLED_writeDPI(x+3, y-3, 1);
  }else{
    OLED_writeDPI(x+1, y-1, 0);
    OLED_writeDPI(x+2, y-2, 0);
    OLED_writeDPI(x+3, y-3, 0);
  }

  if(irR5){
    OLED_writeDPI(x+1, y, 1);
    OLED_writeDPI(x+2, y, 1);
    OLED_writeDPI(x+3, y, 1);
  }else{
    OLED_writeDPI(x+1, y, 0);
    OLED_writeDPI(x+2, y, 0);
    OLED_writeDPI(x+3, y, 0);
  }
}

char start_run(){
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
  char x=70,y=5;
  OLED_writeDPI(x, y, 1);
  OLED_writeDPI(x+1, y+1, 1);
  OLED_writeDPI(x-1, y+1, 1);
  OLED_writeDPI(x, y+1, 1);
  while(1){
    if(!HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)){
      while(!HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)){
        HAL_Delay(1000);
        if(!HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)){
          return 0;
        }
      }
      break;
    }
    flash_OLED_ir();
  }
  return 1;
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
  char nextDir = 0; //下一步绝对方�??????????
  char backFlag = 0; //下一步绝对方�??????????

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, &RxBuffer1, 1);
  HAL_UART_Receive_IT(&huart2, &RxBuffer2, 1);
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);

  OLED_Init();
  OLED_Clear();
  para_init(&carInfo, 1, 1, 1);
  flash_OLED_maze();
  flash_OLED_carPos(carInfo);

  debug = start_run();
  if(debug){
    OLED_ShowString(70,5,"Debug  ",12);
  }else{
    OLED_ShowString(70,5,"Run... ",12);
  }
//  uint8_t str[] = "Run... ";

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    char flag = 0;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if(debug && !HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)){
      while(!HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin));

      if(sprintFlag == 0){  //探索阶段
        nextDir = search_dir(carInfo); //根据是否有墙和是否走过得出下�??????????步的方向
        backFlag = 0;
      }else {  //冲刺阶段
        nextDir = bestPath(dirStack, &dirStackIdx); //根据计算得出的最优路径得出下�??????????步的方向
        if(nextDir == 255){ //ENDOFCODE
          HAL_TIM_Base_Stop_IT(&htim6);
          HAL_TIM_Base_Stop_IT(&htim7);
          OLED_ShowString(70,5,"FINISH ",12);
          while(1);
        }
      }

      if(nextDir == 255){ //如果无法得出下一步方向，进行回溯
        nextDir = backtrack(dirStack, &dirStackIdx);
        backFlag = 1;
        if(nextDir == 255){ //如果回溯栈空，说明以遍历回起点，准备冲刺
          dirStackIdx = creat_bestPath(carInfo, maze, dirStack);  //计算�????优路�????
          sprintFlag = 1; //切换冲刺标记
        }
      }

      go_to_next(carInfo, nextDir);  //执行

      /*刷新信息*/
      if(!backFlag) flash_pathStack(nextDir); //刷新方向�??????????
      flash_mapPathInfo(carInfo, nextDir); //刷新地图信息
      flash_carInfo(&carInfo, nextDir); //刷新小车自身信息

      /*刷新OLED*/
      flash_OLED_maze();
      flash_OLED_carPos(carInfo);
    }
    flash_OLED_ir();
  }
  /* USER CODE END 3 */
}

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
    if(!debug){
      if(irR2){
        chanLM(8);
      }else if(irR4){
        chanRM(8);
      }
    }
  }
  if (htim->Instance == htim7.Instance){ //10ms
    static uint8_t flag = 0;
    static uint8_t num = 1;

    if(!flag){
      ir_on(num);
    }else{
      if(num==1){
        if(HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin))  irR1 = 0;
        else irR1 = 1;
      }else if(num==2){
        if(HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin))  irR2 = 0;
        else irR2 = 1;
      }else if(num==3){
        if(HAL_GPIO_ReadPin(IR3_GPIO_Port, IR3_Pin))  irR3 = 0;
        else irR3 = 1;
      }else if(num==4){
        if(HAL_GPIO_ReadPin(IR4_GPIO_Port, IR4_Pin))  irR4 = 0;
        else irR4 = 1;
      }else if(num==5){
        if(HAL_GPIO_ReadPin(IR5_GPIO_Port, IR5_Pin))  irR5 = 0;
        else irR5 = 1;
      }
    }

    if(flag)  num++;
    if(num>5) num=0;
    flag = !flag;
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){ //串口接收中断
  if(huart == &huart2){
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); //翻转LED
    HAL_UART_Transmit(&huart2, &RxBuffer2, sizeof(uint8_t), 100);
    HAL_UART_Receive_IT(&huart2, &RxBuffer2, 1);
  }
  if(huart == &huart1){
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); //翻转LED
    HAL_UART_Transmit(&huart1, &RxBuffer1, sizeof(uint8_t), 100);
    HAL_UART_Receive_IT(&huart1, &RxBuffer1, 1);
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
