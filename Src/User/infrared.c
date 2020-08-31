//
// Created by Cause_Hhc on 2020/8/24.
//

#include "infrared.h"

/** 绝对方向：       相对方向：
  *     0           0：直行
  * 3       1       1：右转
  *     2           2：掉头
  *                 3：左转
**/

char irR1=0, irR2=0, irR3=0, irR4=0, irR5=0;

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

char read_DirIr(char relDir){
  if(relDir == 0) return irR1;
  if(relDir == 1) return irR5;
  if(relDir == 3) return irR3;
  return -1;
}