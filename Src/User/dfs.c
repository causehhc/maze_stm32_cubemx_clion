//
// Created by Cause_Hhc on 2020/9/7.
//

#include "dfs.h"

void init_stack(char dirStack[]){
  for(char i=0; i<STKDEEP; i++) dirStack[i] = -1;
}

/* 刷新方向栈*/
void flash_pathStack(char dirStack[], int *dirStackIdx, char dir){
  dirStack[(*dirStackIdx)++] = dir;
}
