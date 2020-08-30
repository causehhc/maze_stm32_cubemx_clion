//
// Created by Cause_Hhc on 2020/8/24.
//

#include "infrared.h"

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

char check_IR(char num){
  char res = -1;
  if(num == 1){
    res = HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin);
  }
  if(num == 2){
    res = HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin);
  }
  if(num == 3){
    res = HAL_GPIO_ReadPin(IR3_GPIO_Port, IR3_Pin);
  }
  if(num == 4){
    res = HAL_GPIO_ReadPin(IR4_GPIO_Port, IR4_Pin);
  }
  if(num == 5){
    res = HAL_GPIO_ReadPin(IR5_GPIO_Port, IR5_Pin);
  }
  return res;
}

char read_DirIr(char relDir){
  if(relDir == 0) return check_IR(3);
  if(relDir == 1) return check_IR(5);
  if(relDir == 3) return check_IR(1);
  return -1;
}