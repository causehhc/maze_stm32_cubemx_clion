//
// Created by Cause_Hhc on 2020/8/24.
//

#include "maze.h"

char checkAbsDir(char now_x, char now_y, char aim_x, char aim_y){
  if(aim_x-now_x == 1 && aim_y-now_y == 0)  return 0;
  if(aim_x-now_x == 0 && aim_y-now_y == -1) return 1;
  if(aim_x-now_x == -1 && aim_y-now_y == 0) return 2;
  if(aim_x-now_x == 0 && aim_y-now_y == 1) return 3;
  return 4;
}

char checkNextDir(char relDir, char absDir){
  if(absDir == 2) relDir += 2;
  if(absDir == 1) relDir ++;
  if(absDir == 3) relDir --;
  if(relDir < 0)  relDir += 4;
  if(relDir > 3)  relDir -= 4;
  return relDir;
}

