//
// Created by Cause_Hhc on 2020/8/24.
//

#include "maze.h"
#include "queue.h"
#include <stdio.h>

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
  if(absDir == 0) res &= maze[carInfo.x][carInfo.y-2];
  if(absDir == 1) res &= maze[carInfo.x+2][carInfo.y];
  if(absDir == 2) res &= maze[carInfo.x][carInfo.y+2];
  if(absDir == 3) res &= maze[carInfo.x-2][carInfo.y];
  return res>>4;
}

/* 写入地图墙壁信息*/
void write_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val){
  static uint8_t temp = 0;
  if(val) temp = 0x11;
  else temp = 0x10;
  if(absDir == 0) {
    maze[carInfo.x][carInfo.y-1] &= temp;
    maze[carInfo.x][carInfo.y-2] &= temp;
  }
  if(absDir == 1) {
    maze[carInfo.x+1][carInfo.y] &= temp;
    maze[carInfo.x+2][carInfo.y] &= temp;
  }
  if(absDir == 2) {
    maze[carInfo.x][carInfo.y+1] &= temp;
    maze[carInfo.x][carInfo.y+2] &= temp;
  }
  if(absDir == 3) {
    maze[carInfo.x-1][carInfo.y] &= temp;
    maze[carInfo.x-2][carInfo.y] &= temp;
  }
}

/* 写入地图路径信息*/
void write_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val){
  static uint8_t temp = 0;
  if(val) temp = 0x11;
  else temp = 0x01;
  if(absDir == 0) {
    maze[carInfo.x][carInfo.y-1] &= temp;
    maze[carInfo.x][carInfo.y-2] &= temp;
  }
  if(absDir == 1) {
    maze[carInfo.x+1][carInfo.y] &= temp;
    maze[carInfo.x+2][carInfo.y] &= temp;
  }
  if(absDir == 2) {
    maze[carInfo.x][carInfo.y+1] &= temp;
    maze[carInfo.x][carInfo.y+2] &= temp;
  }
  if(absDir == 3) {
    maze[carInfo.x-1][carInfo.y] &= temp;
    maze[carInfo.x-2][carInfo.y] &= temp;
  }
}

/* 回溯方向栈*/
char backtrack(char *dirStack, int *dirStackIdx){
  char backDir = -1;
  if(--(*dirStackIdx) != -1){
    backDir = dirStack[*dirStackIdx];
    dirStack[(*dirStackIdx)] = -1;
    if(backDir >= 0) backDir += 2;
    if(backDir >= 4) backDir -= 4;
  }
  return backDir;
}

/* 前往下一个最优路径*/
char bestPath(char *dirStack, int *dirStackIdx){
  if(*dirStackIdx == -1){
    return -1;
  }
  return dirStack[(*dirStackIdx)--];
}

void initTable(char highTable[HIDPI][HIDPI]){
  for(char x=0;x<HIDPI;x++){
    for(char y=0;y<HIDPI;y++){
      highTable[x][y] = -1;
    }
  }
}

char isConnect(uint8_t maze[DPI][DPI], char newX,char newY, char absDir){
  char flag = 1;
  if(absDir==0){
    newY++;
  }else if(absDir==1){
    newX--;
  }else if(absDir==2){
    newY--;
  }else if(absDir==3){
    newX++;
  }
  if(maze[newX][newY] & 0x01){
    flag = 0;
  }
  if(newX>127 || newY>127){
    flag = 0;
  }
  if(newX==0 || newY==0){
    flag = 0;
  }
  if(newX==HIDPI || newY==HIDPI){
    flag = 0;
  }
  return flag;
}

void trans(uint8_t maze[DPI][DPI]){
  for(char x=0; x<DPI; x++){
    printf("=====");
  }
  printf("\n");
  for(char y=0; y<DPI; y++){
    for(char x=0; x<DPI; x++){
      printf("%d\t", maze[x][y]);
    }
    printf("\n");
  }
}
void trans2(char highTable[HIDPI][HIDPI]){
  for(char x=0; x<HIDPI; x++){
    printf("=====");
  }
  printf("\n");
  for(char y=0; y<HIDPI; y++){
    for(char x=0; x<HIDPI; x++){
      printf("%d\t", highTable[x][y]);
    }
    printf("\n");
  }
}

void test(uint8_t maze[DPI][DPI]){
  maze[1][1] = 0;
  maze[2][1] = 0;
  maze[3][1] = 0;
  maze[3][2] = 0;
  maze[3][3] = 0;
  maze[2][3] = 0;
  maze[1][3] = 0;
  maze[4][3] = 0;
  maze[5][3] = 0;
}

/* 创建最优路径*/
char creat_bestPath(carInfoType carInfo, uint8_t maze[DPI][DPI], char *dirStack){
//  test(maze);
  trans(maze);

  Queue *q = initQueue();
  type pos;
  pos.x = carInfo.x;
  pos.y = carInfo.y;
  queue_offer(q, pos);

  char highTable[HIDPI][HIDPI] = {-1};
  initTable(highTable);
  highTable[pos.x][pos.y] = 0;

  while(!isEmpty(q)){
    type tempPos = queue_poll(q);
    for(char absDir=0; absDir<4; absDir++) {
      char newX = tempPos.x;
      char newY = tempPos.y;
      if (absDir == 0) newY = tempPos.y - 1;
      else if (absDir == 1) newX = tempPos.x + 1;
      else if (absDir == 2) newY = tempPos.y + 1;
      else if (absDir == 3) newX = tempPos.x - 1;
      if (isConnect(maze, newX*2-1, newY*2-1, absDir)) {
        if (highTable[newX][newY] == 255) {
          pos.x = newX;
          pos.y = newY;
          queue_offer(q, pos);
          highTable[newX][newY] = highTable[tempPos.x][tempPos.y]+1;
        }
      }
    }
  }
  trans2(highTable);
  char idx=0;
  pos.x = ENDX;
  pos.y = ENDY;
  while(!(pos.x==carInfo.x && pos.y==carInfo.y)){
    for(char absDir=0; absDir<4; absDir++) {
      char newX = pos.x;
      char newY = pos.y;
      if (absDir == 0) newY = pos.y - 1;
      else if (absDir == 1) newX = pos.x + 1;
      else if (absDir == 2) newY = pos.y + 1;
      else if (absDir == 3) newX = pos.x - 1;
      if(highTable[newX][newY] == highTable[pos.x][pos.y]-1){
        char backDir = absDir;
        if(backDir >= 0) backDir += 2;
        if(backDir >= 4) backDir -= 4;
        dirStack[idx++] = backDir;
        highTable[pos.x][pos.y] = 200;
        pos.x = newX;
        pos.y = newY;
        break;
      }
    }
  }
  return idx-1;
}
