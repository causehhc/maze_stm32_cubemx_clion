//
// Created by Cause_Hhc on 2020/8/24.
//

#ifndef MAZE_STM32_CUBEMX_CLION_MOTOR_H
#define MAZE_STM32_CUBEMX_CLION_MOTOR_H
#include "tim.h"

void check_ENC(motorInfoType *leftInfo, motorInfoType *rightInfo);
void plus_ADD(motorInfoType *leftInfo, motorInfoType *rightInfo);
void incremental_PI_A(motorInfoType *leftInfo);
void incremental_PI_B(motorInfoType *rightInfo);
void range_PWM(motorInfoType *leftInfo, motorInfoType *rightInfo, int amplitude);
void set_PWM(motorInfoType *leftInfo, motorInfoType *rightInfo);
void go_straight(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth, int mul);
void go_left(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth, int mul);
void go_right(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth, int mul);
void go_turn(motorInfoType *leftInfo, motorInfoType *rightInfo, int lenth, int mul);
void go_stop(motorInfoType *leftInfo, motorInfoType *rightInfo);

#endif //MAZE_STM32_CUBEMX_CLION_MOTOR_H
