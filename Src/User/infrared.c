//
// Created by Cause_Hhc on 2020/8/24.
//

#include "infrared.h"

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