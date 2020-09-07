//
// Created by Cause_Hhc on 2020/9/7.
//

#ifndef MAZE_STM32_CUBEMX_CLION_DFS_H
#define MAZE_STM32_CUBEMX_CLION_DFS_H

#include "main.h"

void init_stack(char dirStack[]);
char back_track(char *dirStack, int *dirStackIdx);
void flash_pathStack(char dirStack[], int *dirStackIdx, char dir);

#endif //MAZE_STM32_CUBEMX_CLION_DFS_H
