//
// Created by Cause_Hhc on 2020/8/24.
//

#include "infrared.h"

void check_edge(char x, char y, char relDir, char **maze){
  if(HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin)){
    if(relDir == 1) maze[x][y-1] |= 0x00;
    if(relDir == 2) maze[x-1][y] |= 0x00;
    if(relDir == 3) maze[x][y+1] |= 0x00;
    if(relDir == 4) maze[x+1][y] |= 0x00;
  }
  if(HAL_GPIO_ReadPin(IR3_GPIO_Port, IR3_Pin)){
    if(relDir == 1) maze[x+1][y] |= 0x00;
    if(relDir == 2) maze[x][y-1] |= 0x00;
    if(relDir == 3) maze[x-1][y] |= 0x00;
    if(relDir == 4) maze[x][y+1] |= 0x00;
  }
  if(HAL_GPIO_ReadPin(IR5_GPIO_Port, IR5_Pin)){
    if(relDir == 1) maze[x][y+1] |= 0x00;
    if(relDir == 2) maze[x+1][y] |= 0x00;
    if(relDir == 3) maze[x][y-1] |= 0x00;
    if(relDir == 4) maze[x-1][y] |= 0x00;
  }
}
