//
// Created by Cause_Hhc on 2020/8/24.
//

#include "motor.h"

float Velocity_KP_A = 10,Velocity_KI_A = 10;
int Bias_A,Pwm_A,Last_bias_A;
float Velocity_KP_B = 10,Velocity_KI_B = 10;
int Bias_B,Pwm_B,Last_bias_B;

void check_ENC(motorInfoType *leftInfo, motorInfoType *rightInfo){
  leftInfo->ENC = (short)__HAL_TIM_GET_COUNTER(&htim3);
  __HAL_TIM_SET_COUNTER(&htim3, 0);
  rightInfo->ENC = (short)__HAL_TIM_GET_COUNTER(&htim4);
  __HAL_TIM_SET_COUNTER(&htim4, 0);
}

void plus_ADD(motorInfoType *leftInfo, motorInfoType *rightInfo){
  leftInfo->ADD += leftInfo->ENC;
  rightInfo->ADD += leftInfo->ENC;
}

void incremental_PI_A(motorInfoType *leftInfo){
  Bias_A= leftInfo->TGT - leftInfo->ENC;
  Pwm_A += Velocity_KP_A * (Bias_A - Last_bias_A) + Velocity_KI_A * Bias_A;
  if(Pwm_A > 7200)Pwm_A=7200;
  if(Pwm_A < -7200)Pwm_A=-7200;
  Last_bias_A=Bias_A;
  leftInfo->PWM = Pwm_A;
}

void incremental_PI_B(motorInfoType *rightInfo){
  Bias_B= rightInfo->TGT - rightInfo->ENC;
  Pwm_B += Velocity_KP_B * (Bias_B - Last_bias_B) + Velocity_KI_B * Bias_B;
  if(Pwm_B > 7200)Pwm_B=7200;
  if(Pwm_B < -7200)Pwm_B=-7200;
  Last_bias_B=Bias_B;
  rightInfo->PWM = Pwm_B;
}

void range_PWM(motorInfoType *leftInfo, motorInfoType *rightInfo, int amplitude){
  if(leftInfo->PWM < -amplitude) leftInfo->PWM = -amplitude;
  if(leftInfo->PWM > amplitude) leftInfo->PWM = amplitude;
  if(rightInfo->PWM < -amplitude) rightInfo->PWM = -amplitude;
  if(rightInfo->PWM > amplitude) rightInfo->PWM = amplitude;
}

void set_PWM(motorInfoType *leftInfo, motorInfoType *rightInfo){
  if(leftInfo->PWM >= 0){
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, leftInfo->PWM);
  }else{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 7200);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 7200 + leftInfo->PWM);
  }

  if(rightInfo->PWM >= 0){
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, rightInfo->PWM);
  }else{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 7200);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 7200 + rightInfo->PWM);
  }
}

void go_straight(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth){
  leftInfo->TGT = 10;
  rightInfo->TGT = 10;
  while(leftInfo->ADD > lenth && rightInfo->ADD > lenth);
}

void go_left(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth){
  leftInfo->TGT = -10;
  rightInfo->TGT = 10;
  while(leftInfo->ADD > lenth && rightInfo->ADD > lenth);
}

void go_right(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth){
  leftInfo->TGT = 10;
  rightInfo->TGT = -10;
  while(leftInfo->ADD > lenth && rightInfo->ADD > lenth);
}

void go_turn(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth){
  leftInfo->TGT = 10;
  rightInfo->TGT = -10;
  while(leftInfo->ADD > lenth && rightInfo->ADD > lenth);
}
