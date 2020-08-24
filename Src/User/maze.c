//
// Created by Cause_Hhc on 2020/8/24.
//

#include "maze.h"

char checkAbsDir(positionVar *pos_var){
  if(pos_var->aim_x-pos_var->x == 1 && pos_var->aim_y-pos_var->y == 0)  return 1;
  if(pos_var->aim_x-pos_var->x == 0 && pos_var->aim_y-pos_var->y == -1) return 2;
  if(pos_var->aim_x-pos_var->x == -1 && pos_var->aim_y-pos_var->y == 0) return 3;
  if(pos_var->aim_x-pos_var->x == 0 && pos_var->aim_y-pos_var->y == 1) return 4;
  return 0;
}

char checkNextDir(char relDir, char absDir){
  if(absDir == 3) relDir += 2;
  if(absDir == 2) relDir ++;
  if(absDir == 4) relDir --;
  if(relDir < 1)  relDir += 4;
  if(relDir > 4)  relDir -= 4;
  return relDir;
}

