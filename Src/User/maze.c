//
// Created by Cause_Hhc on 2020/8/24.
//

#include "maze.h"

/** 绝对方向：       相对方向：
  *     0           0：直行
  * 3       1       1：右转
  *     2           2：掉头
  *                 3：左转
**/

/* 相对方向->绝对方向*/
char rel_to_abs(char nowAbsDir, char relDir){
  return (relDir + nowAbsDir) % 4;
}

/* 绝对方向->绝对方向*/
char abs_to_rel(char nowAbsDir, char absDir){
  return (absDir - nowAbsDir) % 4;
}

/* 读取地图墙壁信息*/
char read_map_wall(uint8_t **maze, carInfoType carInfo, char absDir){
  char res = 0x01;
  if(absDir == 0) res &= maze[carInfo.x][carInfo.y-1];
  if(absDir == 1) res &= maze[carInfo.x+1][carInfo.y];
  if(absDir == 2) res &= maze[carInfo.x][carInfo.y+1];
  if(absDir == 3) res &= maze[carInfo.x-1][carInfo.y];
  return res;
}

/* 读取地图路径信息*/
char read_map_path(uint8_t **maze, carInfoType carInfo, char absDir){
  char res = 0x10;
  if(absDir == 0) res &= maze[carInfo.x][carInfo.y-1];
  if(absDir == 1) res &= maze[carInfo.x+1][carInfo.y];
  if(absDir == 2) res &= maze[carInfo.x][carInfo.y+1];
  if(absDir == 3) res &= maze[carInfo.x-1][carInfo.y];
  return res>>4;
}

/* 写入地图墙壁信息*/
void write_map_wall(uint8_t **maze, carInfoType carInfo, char absDir, char val){
  if(absDir == 0) maze[carInfo.x][carInfo.y-1] |= val;
  if(absDir == 1) maze[carInfo.x+1][carInfo.y] |= val;
  if(absDir == 2) maze[carInfo.x][carInfo.y+1] |= val;
  if(absDir == 3) maze[carInfo.x-1][carInfo.y] |= val;
}

/* 写入地图路径信息*/
void write_map_path(uint8_t **maze, carInfoType carInfo, char absDir, char val){
  if(absDir == 0) maze[carInfo.x][carInfo.y-1] |= (val<<4);
  if(absDir == 1) maze[carInfo.x+1][carInfo.y] |= (val<<4);
  if(absDir == 2) maze[carInfo.x][carInfo.y+1] |= (val<<4);
  if(absDir == 3) maze[carInfo.x-1][carInfo.y] |= (val<<4);
}

/* 回溯方向栈*/
char backtrack(char *dirStack, int *dirStackIdx){
  char backDir = 0;
  if(--(*dirStackIdx) != -1){
    backDir = dirStack[*dirStackIdx];
    if(backDir >= 0) backDir += 2;
    if(backDir >= 4) backDir -= 4;
  }
  return backDir;
}

/* 前往下一个最优路径*/
char bestPath(char *dirStack, int *dirStackIdx){
  return dirStack[(*dirStackIdx)++];
}

/* 创建最优路径*/
void creat_bestPath(carInfoType carInfo, uint8_t **maze, char *dirStack){
  char highTable[DPI][DPI] = {-1};
  char height = 0;
  char dirQueue[99] = {-1};
  char dirQueueIdx = 0;

  dirQueue[dirQueueIdx++] = 1;
  while(dirQueueIdx != 0){
    char heightAddFlag = 0;
    char tempDir = dirQueue[dirQueueIdx--];
    for(char absDir=0; absDir<4; absDir++){
      if(isConnect(nowX, nowY, newX, newY)){
        if(height[newX][newY] == -1){
          heightAddFlag = 1;
          dirQueue[dirQueueIdx++] = absDir;
          highTable[newX][newY] = height;
        }
      }
    }
    if(heightAddFlag) height++;
  }
}
