//
// Created by 43852 on 2020/9/4.
//
#include "stepMotor.h"
#include "gpio.h"
#include "tim.h"
unsigned char forward[]={0x11,0x33,0x22,0x66,0x44,0xcc,0x88,0x99};//����ͬʱ��ת
unsigned char reverse[]={0x11,0x99,0x88,0xcc,0x44,0x66,0x22,0x33};//����ͬʱ��ת
unsigned char for_rev[]={0x11,0x93,0x82,0xc6,0x44,0x6c,0x28,0x39};//�����ҷ�
unsigned char rev_for[]={0x11,0x39,0x28,0x6c,0x44,0xc6,0x82,0x93};//������
unsigned char i,j;

void fuzhi(unsigned char temp){
  if(temp&0x01) HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, GPIO_PIN_RESET);
  if(temp&0x02) HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, GPIO_PIN_RESET);
  if(temp&0x04) HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, GPIO_PIN_RESET);
  if(temp&0x08) HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, GPIO_PIN_RESET);

  if(temp&0x10) HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
  if(temp&0x20) HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
  if(temp&0x40) HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
  if(temp&0x80) HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
}

void go_straight(char num)      //直走
{
  for(j=0;j<num;j++)
  {
    for(i=0;i<8;i++)
    {
      fuzhi(for_rev[i]);

      HAL_Delay(1);

    }
  }
}

void go_left(char num)   //左转
{
  for(j=0;j<num;j++)
  {
    for(i=0;i<8;i++)
    {
      fuzhi(reverse[i]);
      HAL_Delay(1);
    }
  }
}

void go_right(char num)   //右转
{
  for(j=0;j<num;j++)
  {
    for(i=0;i<8;i++)
    {
      fuzhi(forward[i]);
      HAL_Delay(1);
    }
  }
}

void go_turn(char num)      //后转
{
  for(j=0;j<99;j++)
  {
    for(i=0;i<8;i++)
    {
      fuzhi(forward[i]);
      HAL_Delay(1);
    }
  }
}

void chanLM(char num)   //左修正
{
  for(i=0;i<8;i++)
  {
    fuzhi(forward[i]|0xf0);
    HAL_Delay(1);
  }
}

void chanRM(char num)   //右修正
{
  for(i=0;i<8;i++)
  {
    fuzhi(reverse[i]|0x0f);
    HAL_Delay(1);
  }
}
