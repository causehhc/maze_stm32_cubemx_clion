//
// Created by Cause_Hhc on 2020/9/7.
//

#include "dfs.h"

/*初始化方向栈*/
void init_stack(char dirStack[]){
  for(char i=0; i<STKDEEP; i++) dirStack[i] = -1;
}

/*回溯方向栈*/
char back_track(char *dirStack, int *dirStackIdx){
  char backDir = -1;
  if(--(*dirStackIdx) != -1){
    backDir = dirStack[*dirStackIdx];
    dirStack[(*dirStackIdx)] = -1;
    if(backDir >= 0) backDir += 2;
    if(backDir >= 4) backDir -= 4;
  }
  return backDir;
}

/* 刷新方向栈*/
void flash_pathStack(char dirStack[], int *dirStackIdx, char dir){
  dirStack[(*dirStackIdx)++] = dir;
}
