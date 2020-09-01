//
// Created by Cause_Hhc on 2020/8/24.
//

#ifndef MAZE_STM32_CUBEMX_CLION_MAZE_H
#define MAZE_STM32_CUBEMX_CLION_MAZE_H
#include <math.h>
#include "main.h"

#define DPI 16
#define STKDEEP 200
#define MAZELENTH 128 //xmm
#define PASSWIDTH 128 //xmm
#define WALLWIDTH 128 //xmm
#define CARLENTH 10.0 //xmm
#define CARWIDTH 10.0 //xmm

typedef struct {
    char x; //坐标x
    char y; //坐标y
    char dir; //绝对方向
}carInfoType;

char rel_to_abs(char nowAbsDir, char relDir);
char abs_to_rel(char nowAbsDir, char absDir);
char read_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir);
char read_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir);
void write_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val);
void write_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val);
void init_maze(uint8_t maze[DPI][DPI]);
void init_stack(char dirStack[STKDEEP]);

char backtrack(char *dirStack, int *dirStackIdx);
char bestPath(char *dirStack, int *dirStackIdx);
void creat_bestPath(carInfoType carInfo, uint8_t maze[DPI][DPI], char *dirStack);
void creat_bestPath_test(carInfoType carInfo, uint8_t maze[DPI][DPI], char *dirStack);

#endif //MAZE_STM32_CUBEMX_CLION_MAZE_H
