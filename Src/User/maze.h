//
// Created by Cause_Hhc on 2020/8/24.
//

#ifndef MAZE_STM32_CUBEMX_CLION_MAZE_H
#define MAZE_STM32_CUBEMX_CLION_MAZE_H
#include <math.h>

#define DPI 16
#define MAZELENTH 128 //xmm
#define PASSWIDTH 128 //xmm
#define WALLWIDTH 128 //xmm
#define CARLENTH 10.0 //xmm
#define CARWIDTH 10.0 //xmm

typedef struct {
    char x;
    char y;
    char aim_x;
    char aim_y;
    char relDir; //相对方向
}positionVar;

char checkAbsDir(positionVar *pos_var);
char checkNextDir(char relDir, char absDir);
#endif //MAZE_STM32_CUBEMX_CLION_MAZE_H
