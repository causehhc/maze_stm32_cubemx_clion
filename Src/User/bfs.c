//
// Created by Cause_Hhc on 2020/9/7.
//

#include "bfs.h"
#include "queue.h"
#include <stdio.h>

/*回溯方向栈*/
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

/*前往下一个最优路径*/
char bestPath(char *dirStack, int *dirStackIdx){
  if(*dirStackIdx == -1) return -1;
  return dirStack[(*dirStackIdx)--];
}

/*初始化等高表*/
void initTable(char highTable[HIGHDPI][HIGHDPI]){
  for(char x=0; x < HIGHDPI; x++){
    for(char y=0; y < HIGHDPI; y++){
      highTable[x][y] = -1;
    }
  }
}

/*判断地图之间的连接性*/
char isConnect(uint8_t maze[DPI][DPI], char newX,char newY, char absDir){
  char flag = 1;
  if(absDir==0) newY++;
  else if(absDir==1) newX--;
  else if(absDir==2) newY--;
  else if(absDir==3) newX++;

  if(maze[newX][newY] & 0x01) flag = 0;
  if(newX>127 || newY>127) flag = 0;
  if(newX==0 || newY==0) flag = 0;
  if(newX == HIGHDPI || newY == HIGHDPI) flag = 0;
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
void trans2(char highTable[HIGHDPI][HIGHDPI]){
  for(char x=0; x < HIGHDPI; x++){
    printf("=====");
  }
  printf("\n");
  for(char y=0; y < HIGHDPI; y++){
    for(char x=0; x < HIGHDPI; x++){
      printf("%d\t", highTable[x][y]);
    }
    printf("\n");
  }
}

/*创建最优路径*/
char creat_bestPath(carInfoType carInfo, uint8_t maze[DPI][DPI], char *dirStack){
  trans(maze);

  Queue *q = initQueue();
  type pos;
  pos.x = carInfo.x;
  pos.y = carInfo.y;
  queue_offer(q, pos);

  char highTable[HIGHDPI][HIGHDPI] = {-1};
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