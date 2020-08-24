//
// Created by Cause_Hhc on 2020/8/24.
//

#include "maze.h"

void check_offset(int *left, int *right, positionVar *pos_var){
  static double a = 0;
  double x = (double)*left;
  double y = (double)*right;
  a = (x-y)/CARWIDTH;
  pos_var->relDir += a;
  pos_var->offset = (int)(sin(a)*(y/a+CARWIDTH/2)/cos(a/2));
  *left = 0;
  *right = 0;
}

void check_pos(positionVar *pos_var){
  pos_var->x += (int)(pos_var->offset * cos(pos_var->relDir));
  pos_var->y += (int)(pos_var->offset * sin(pos_var->relDir));
}
