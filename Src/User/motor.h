//
// Created by Cause_Hhc on 2020/8/24.
//

#ifndef MAZE_STM32_CUBEMX_CLION_MOTOR_H
#define MAZE_STM32_CUBEMX_CLION_MOTOR_H
#include "tim.h"

typedef struct {
    int ENC;
    int PWM;
    int ADD;
    int TGT;
}motorVar;

float Velocity_KP_A = 10,Velocity_KI_A = 10;
int Bias_A,Pwm_A,Last_bias_A;
float Velocity_KP_B = 10,Velocity_KI_B = 10;
int Bias_B,Pwm_B,Last_bias_B;

void check_ENC(motorVar *left_var, motorVar *right_var);
void plus_ADD(motorVar *left_var, motorVar *right_var);
void incremental_PI_A(motorVar *left_var);
void incremental_PI_B(motorVar *right_var);
void range_PWM(motorVar *left_var, motorVar *right_var, int amplitude);
void set_PWM(motorVar *left_var, motorVar *right_var);
void go_straight(motorVar *left_var, motorVar *right_var, int lenth);
void go_left(motorVar *left_var, motorVar *right_var, int lenth);
void go_right(motorVar *left_var, motorVar *right_var, int lenth);
void go_turn(motorVar *left_var, motorVar *right_var, int lenth);

#endif //MAZE_STM32_CUBEMX_CLION_MOTOR_H
