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
//新路�??????1，有墙是1

void init_maze(uint8_t maze[DPI][DPI]){
  for(char x=0; x<DPI; x++) {
    for (char y = 0; y < DPI; y++) {
      maze[x][y] = 0x11;
    }
  }
  for(char i=0; i<DPI; i++) {
    maze[0][i] = 0x01;
  }
  for(char i=0; i<DPI; i++) {
    maze[DPI-1][i] = 0x01;
  }
  for(char i=0; i<DPI; i++) {
    maze[i][0] = 0x01;
  }
  for(char i=0; i<DPI; i++) {
    maze[i][DPI-1] = 0x01;
  }
}
void init_stack(char dirStack[]){
  for(char i=0; i<STKDEEP; i++) {
    dirStack[i] = -1;
  }
}

/* 相对方向->绝对方向*/
char rel_to_abs(char nowAbsDir, char relDir){
  return (relDir + nowAbsDir) % 4;
}

/* 绝对方向->相对方向*/
char abs_to_rel(char nowAbsDir, char absDir){
  static char temp = 0;
  temp = (absDir - nowAbsDir) % 4;
  if(temp>127)	temp += 4;
  return temp;
}

/* 读取地图墙壁信息*/
char read_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir){
  char res = 0x01;
  if(absDir == 0) res &= maze[carInfo.x][carInfo.y-1];
  if(absDir == 1) res &= maze[carInfo.x+1][carInfo.y];
  if(absDir == 2) res &= maze[carInfo.x][carInfo.y+1];
  if(absDir == 3) res &= maze[carInfo.x-1][carInfo.y];
  return res;
}

/* 读取地图路径信息*/
char read_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir){
  char res = 0x10;
  if(absDir == 0) res &= maze[carInfo.x][carInfo.y-1];
  if(absDir == 1) res &= maze[carInfo.x+1][carInfo.y];
  if(absDir == 2) res &= maze[carInfo.x][carInfo.y+1];
  if(absDir == 3) res &= maze[carInfo.x-1][carInfo.y];
  return res>>4;
}

/* 写入地图墙壁信息*/
void write_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val){
  static uint8_t temp = 0;
  if(val) temp = 0x11;
  else temp = 0x10;
  if(absDir == 0) maze[carInfo.x][carInfo.y-1] &= temp;
  if(absDir == 1) maze[carInfo.x+1][carInfo.y] &= temp;
  if(absDir == 2) maze[carInfo.x][carInfo.y+1] &= temp;
  if(absDir == 3) maze[carInfo.x-1][carInfo.y] &= temp;
}

/* 写入地图路径信息*/
void write_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val){
  static uint8_t temp = 0;
  if(val) temp = 0x11;
  else temp = 0x01;
  if(absDir == 0) maze[carInfo.x][carInfo.y-1] &= temp;
  if(absDir == 1) maze[carInfo.x+1][carInfo.y] &= temp;
  if(absDir == 2) maze[carInfo.x][carInfo.y+1] &= temp;
  if(absDir == 3) maze[carInfo.x-1][carInfo.y] &= temp;
}

/* 回溯方向栈*/
char backtrack(char *dirStack, int *dirStackIdx){
  char backDir = -1;
  if(--(*dirStackIdx) != -1){
    backDir = dirStack[*dirStackIdx];
    if(backDir >= 0) backDir += 2;
    if(backDir >= 4) backDir -= 4;
  }
  return backDir;
}

/* 前往下一个最优路径*/
char bestPath(char *dirStack, int *dirStackIdx){
  if(*dirStackIdx == STKDEEP){
    return -1;
  }
  return dirStack[++(*dirStackIdx)];
}

char isConnect(uint8_t maze[DPI][DPI], char nowX,char nowY,char newX,char newY){
  if(maze[newY][newY] & 0x01){
    return 0;
  }
  return 1;
}

/* 创建最优路径*/
void creat_bestPath(carInfoType carInfo, uint8_t maze[DPI][DPI], char *dirStack){
  char highTable[DPI][DPI] = {-1};
  for(char x=0;x<DPI;x++){
    for(char y=0;y<DPI;y++){
      highTable[x][y] = -1;
    }
  }
  char height = 0;
  char dirQueue[STKDEEP] = {-1};
  char dirQueueIdx = 0;

  char nowX = carInfo.x;
  char nowY = carInfo.y;
  char newX = nowX;
  char newY = nowY;

  highTable[nowX][nowY] = height;
  dirQueue[dirQueueIdx++] = 4;
  while(dirQueueIdx != 0){
    char heightAddFlag = 0;
    char tempDir = dirQueue[--dirQueueIdx];
    if(tempDir == 0)  nowY--;
    if(tempDir == 1)  nowX++;
    if(tempDir == 2)  nowY++;
    if(tempDir == 3)  nowX--;
    for(char absDir=0; absDir<4; absDir++){
      newX = nowX;
      newY = nowY;
      if(absDir == 0)  newY = nowY-1;
      if(absDir == 1)  newX = nowX+1;
      if(absDir == 2)  newY = nowY+1;
      if(absDir == 3)  newX = nowX-1;
      if(isConnect(maze, nowX, nowY, newX, newY)){
        if(highTable[newX][newY] == 255){
          heightAddFlag = 1;
          dirQueue[dirQueueIdx++] = absDir;
          highTable[newX][newY] = height;
        }
      }
    }
    if(heightAddFlag) height++;
  }
}

void creat_bestPath_test(carInfoType carInfo, uint8_t maze[DPI][DPI], char *dirStack){
  init_stack(dirStack);
  dirStack[0] = 1;
  dirStack[1] = 2;
  dirStack[2] = 1;
  dirStack[3] = 2;
  dirStack[4] = 1;
  dirStack[5] = 2;
  dirStack[6] = 1;
  dirStack[7] = 2;
  dirStack[8] = 1;
  dirStack[9] = 2;
  dirStack[10] = 1;
  dirStack[11] = 2;
  dirStack[12] = 1;
  dirStack[13] = 2;
  dirStack[14] = 1;
  dirStack[15] = 2;
  dirStack[16] = 1;
  dirStack[17] = 2;
  dirStack[18] = 1;
  dirStack[19] = 2;
}
