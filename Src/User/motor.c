//
// Created by Cause_Hhc on 2020/8/24.
//

#include "motor.h"

void check_ENC(motorVar *left_var, motorVar *right_var){
  left_var->ENC = (short)__HAL_TIM_GET_COUNTER(&htim3);
  __HAL_TIM_SET_COUNTER(&htim3, 0);
  right_var->ENC = (short)__HAL_TIM_GET_COUNTER(&htim4);
  __HAL_TIM_SET_COUNTER(&htim4, 0);
}

void plus_ADD(motorVar *left_var, motorVar *right_var){
  left_var->ADD += left_var->ENC;
  right_var->ADD += left_var->ENC;
}

void incremental_PI_A(motorVar *left_var){
  Bias_A= left_var->TGT - left_var->ENC;
  Pwm_A += Velocity_KP_A * (Bias_A - Last_bias_A) + Velocity_KI_A * Bias_A;
  if(Pwm_A > 7200)Pwm_A=7200;
  if(Pwm_A < -7200)Pwm_A=-7200;
  Last_bias_A=Bias_A;
  left_var->PWM = Pwm_A;
}

void incremental_PI_B(motorVar *right_var){
  Bias_B= right_var->TGT - right_var->ENC;
  Pwm_B += Velocity_KP_B * (Bias_B - Last_bias_B) + Velocity_KI_B * Bias_B;
  if(Pwm_B > 7200)Pwm_B=7200;
  if(Pwm_B < -7200)Pwm_B=-7200;
  Last_bias_B=Bias_B;
  right_var->PWM = Pwm_B;
}

void range_PWM(motorVar *left_var, motorVar *right_var, int amplitude){
  if(left_var->PWM<-amplitude) left_var->PWM = -amplitude;
  if(left_var->PWM>amplitude)  left_var->PWM = amplitude;
  if(right_var->PWM<-amplitude) right_var->PWM = -amplitude;
  if(right_var->PWM>amplitude)  right_var->PWM = amplitude;
}

void set_PWM(motorVar *left_var, motorVar *right_var){
  if(left_var->PWM >= 0){
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, left_var->PWM);
  }else{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 7200);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 7200+left_var->PWM);
  }

  if(right_var->PWM >= 0){
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, right_var->PWM);
  }else{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 7200);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 7200+right_var->PWM);
  }
}
