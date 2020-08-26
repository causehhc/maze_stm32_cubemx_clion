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
    char x; //坐标x
    char y; //坐标y
    char dir; //绝对方向
}carInfoType;

char rel_to_abs(char nowAbsDir, char relDir);
char abs_to_rel(char nowAbsDir, char absDir);
char read_map_wall(char **maze, carInfoType carInfo, char absDir);
char read_map_path(char **maze, carInfoType carInfo, char absDir);
void write_map_wall(char **maze, carInfoType carInfo, char absDir, char val);
void write_map_path(char **maze, carInfoType carInfo, char absDir, char val);

#endif //MAZE_STM32_CUBEMX_CLION_MAZE_H
