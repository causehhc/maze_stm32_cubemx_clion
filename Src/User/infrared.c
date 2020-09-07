//
// Created by Cause_Hhc on 2020/8/24.
//

#include "infrared.h"



extern char irR1, irR2, irR3, irR4, irR5;

/*打开某个ir发射管*/
void ir_on(char num){
  num -= 1;
  if(num&0x01){
    HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, GPIO_PIN_SET);
  }else{
    HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, GPIO_PIN_RESET);
  }
  if(num&0x02){
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_SET);
  }else{
    HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
  }
  if(num&0x04){
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_SET);
  }else{
    HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_RESET);
  }
}

/*读取某个相对方向的ir*/
char read_DirIr(char relDir){
  if(relDir == 0) return irR1;
  if(relDir == 1) return irR5;
  if(relDir == 3) return irR3;
  return -1;
}
