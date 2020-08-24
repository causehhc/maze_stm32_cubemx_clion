//
// Created by Cause_Hhc on 2020/8/24.
//

#ifndef MAZE_STM32_CUBEMX_CLION_MAZE_H
#define MAZE_STM32_CUBEMX_CLION_MAZE_H
#include <math.h>

#define DPI 64
#define MAZELENTH 128 //xmm
#define PASSWIDTH 128 //xmm
#define WALLWIDTH 128 //xmm
#define CARLENTH 10.0 //xmm
#define CARWIDTH 10.0 //xmm

typedef struct {
    char x;
    char y;
    double relDir; //相对方向
    double absDir; //绝对方向
    int offset; //距离上次清0时的中心偏移量
}positionVar;

void check_offset(int *left, int *right, positionVar *pos_var);
void check_pos(positionVar *pos_var);

#endif //MAZE_STM32_CUBEMX_CLION_MAZE_H
