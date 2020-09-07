//
// Created by Cause_Hhc on 2020/8/24.
//

#ifndef MAZE_STM32_CUBEMX_CLION_MAZE_H
#define MAZE_STM32_CUBEMX_CLION_MAZE_H
#include <math.h>
#include "main.h"

char rel_to_abs(char nowAbsDir, char relDir);
char abs_to_rel(char nowAbsDir, char absDir);
void init_maze(uint8_t maze[DPI][DPI]);
char read_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir);
char read_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir);
void write_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val);
void write_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val);
char isEdge(carInfoType carInfo, char absDir);
void flash_mapPathInfo(uint8_t maze[DPI][DPI], carInfoType carInfo, char nextDir);
void flash_carInfo(carInfoType *carInfo, char nextDir);

#endif //MAZE_STM32_CUBEMX_CLION_MAZE_H
