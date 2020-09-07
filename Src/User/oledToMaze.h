//
// Created by Cause_Hhc on 2020/9/7.
//

#ifndef MAZE_STM32_CUBEMX_CLION_OLEDTOMAZE_H
#define MAZE_STM32_CUBEMX_CLION_OLEDTOMAZE_H

#include "oled.h"
#include "maze.h"

void flash_OLED_maze(uint8_t maze[DPI][DPI]);
void flash_OLED_carPos(carInfoType carInfo);
void flash_OLED_ir(char x, char y);

#endif //MAZE_STM32_CUBEMX_CLION_OLEDTOMAZE_H
