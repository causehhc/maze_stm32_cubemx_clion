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
//新路是1，有墙是1

void init_maze(uint8_t maze[DPI][DPI]){
  for(char x=0; x<DPI; x++) {
    for (char y = 0; y < DPI; y++) {
      maze[x][y] = 0x11;
    }
  }
  for(char i=0; i<DPI; i++) maze[0][i] = 0x01;
  for(char i=0; i<DPI; i++) maze[DPI-1][i] = 0x01;
  for(char i=0; i<DPI; i++) maze[i][0] = 0x01;
  for(char i=0; i<DPI; i++) maze[i][DPI-1] = 0x01;
}

/*相对方向->绝对方向*/
char rel_to_abs(char nowAbsDir, char relDir){
  return (relDir + nowAbsDir) % 4;
}

/*绝对方向->相对方向*/
char abs_to_rel(char nowAbsDir, char absDir){
  char temp = 0;
  temp = (absDir - nowAbsDir) % 4;
  if(temp>127)	temp += 4;
  return temp;
}

/*读取地图相关信息*/
char read_map(uint8_t maze[DPI][DPI], char absDir, char x, char y, char res){
  if(absDir == 0) res &= maze[x][y-2];
  if(absDir == 1) res &= maze[x+1][y];
  if(absDir == 2) res &= maze[x][y+2];
  if(absDir == 3) res &= maze[x-1][y];
  return res;
}

/*读取地图墙壁信息*/
char read_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir){
  char res = 0x01;
  res = read_map(maze, absDir, carInfo.x, carInfo.y, res);
  return res;
}

/*读取地图路径信息*/
char read_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir){
  char res = 0x10;
  res = read_map(maze, absDir, carInfo.x, carInfo.y, res);
  return res>>4;
}

/*写入地图相关信息*/
void write_map(uint8_t maze[DPI][DPI], char absDir, char x, char y, uint8_t temp){
  if(absDir == 0) {
    maze[x][y-1] &= temp;
    maze[x][y-2] &= temp;
  }
  if(absDir == 1) {
    maze[x+1][y] &= temp;
    maze[x+2][y] &= temp;
  }
  if(absDir == 2) {
    maze[x][y+1] &= temp;
    maze[x][y+2] &= temp;
  }
  if(absDir == 3) {
    maze[x-1][y] &= temp;
    maze[x-2][y] &= temp;
  }
}

/*写入地图墙壁信息*/
void write_map_wall(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val){
  uint8_t temp = 0;
  if(val) temp = 0x11;
  else temp = 0x10;
  write_map(maze, absDir, carInfo.x, carInfo.y, temp);
}

/*写入地图路径信息*/
void write_map_path(uint8_t maze[DPI][DPI], carInfoType carInfo, char absDir, char val){
  uint8_t temp = 0;
  if(val) temp = 0x11;
  else temp = 0x01;
  write_map(maze, absDir, carInfo.x, carInfo.y, temp);
}

/*迷宫边缘检测*/
char isEdge(carInfoType carInfo, char absDir){
  if(carInfo.y!=1 || absDir!=0){
    if(carInfo.y!=15 || absDir!=2){
      if(carInfo.x!=1 || absDir!=3){
        if(carInfo.x!=15 || absDir!=1){
          return 1;
        }
      }
    }
  }
  return 0;
}

/* 刷新地图路径信息*/
void flash_mapPathInfo(uint8_t maze[DPI][DPI], carInfoType carInfo, char nextDir){
  write_map_path(maze, carInfo, nextDir, 0);
}

/* 刷新小车自身信息*/
void flash_carInfo(carInfoType *carInfo, char nextDir){
  if(nextDir == 0)  carInfo->y-=2;
  if(nextDir == 1)  carInfo->x+=2;
  if(nextDir == 2)  carInfo->y+=2;
  if(nextDir == 3)  carInfo->x-=2;
  if(nextDir != 255 ) carInfo->dir = nextDir;
}



