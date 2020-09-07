//
// Created by Cause_Hhc on 2020/9/7.
//

#ifndef MAZE_STM32_CUBEMX_CLION_BFS_H
#define MAZE_STM32_CUBEMX_CLION_BFS_H

#include "main.h"

char backtrack(char *dirStack, int *dirStackIdx);
char bestPath(char *dirStack, int *dirStackIdx);
char creat_bestPath(carInfoType carInfo, uint8_t maze[DPI][DPI], char *dirStack);

#endif //MAZE_STM32_CUBEMX_CLION_BFS_H
