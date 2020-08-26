//
// Created by Cause_Hhc on 2020/8/24.
//

#include "infrared.h"

char read_IR(char relDir){
  if(relDir == 1){
    return HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin);
  }
  if(relDir == 2){
    return HAL_GPIO_ReadPin(IR3_GPIO_Port, IR3_Pin);
  }
  if(relDir == 3){
    return HAL_GPIO_ReadPin(IR5_GPIO_Port, IR5_Pin);
  }
  return 0;
}