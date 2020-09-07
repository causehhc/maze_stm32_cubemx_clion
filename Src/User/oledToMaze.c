//
// Created by Cause_Hhc on 2020/9/7.
//

#include "oledToMaze.h"

uint8_t oled_buffer[8][128] = {0};
uint8_t oled_val_buffer[128][128] = {0};

extern char irR1, irR2, irR3, irR4, irR5;

void OLED_writeDPI(char x, char y, char val){
  if(oled_val_buffer[x][y] != val){
    OLED_Set_Pos(2+x, y/8);
    if(val == 1)  oled_buffer[y / 8][x] |= (0x01 << (y % 8));
    else oled_buffer[y / 8][x] &= ~(0x01 << (y % 8));
    OLED_WR_DATA(oled_buffer[y / 8][x]);
    oled_val_buffer[x][y] = val;
  }
}

void flash_OLED_maze(uint8_t maze[DPI][DPI]){
  static char val;
  for(char x=0; x<DPI; x++) {
    for (char y = 0; y < DPI; y++) {
      if(maze[x][y] & 0x01) val = 1;
      else  val = 0;
      for (char i = 0; i < LEN / DPI; i++) {
        for (char j = 0; j < LEN / DPI; j++) {
          OLED_writeDPI(i + x * (LEN / DPI), j + y * (LEN / DPI), val);
        }
      }
    }
  }
}

void flash_OLED_carPos(carInfoType carInfo){
  for (char i = 0; i < (LEN / DPI)/2; i++) {
    for (char j = 0; j < (LEN / DPI)/2; j++) {
      OLED_writeDPI(i + carInfo.x*(LEN / DPI)+1, j + carInfo.y*(LEN / DPI)+1, 1);
    }
  }
  if(carInfo.dir == 0){
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1, carInfo.y*(LEN / DPI)+1-1, 1);
  }else if(carInfo.dir == 1){
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1+1, carInfo.y*(LEN / DPI)+1, 1);
  }else if(carInfo.dir == 2){
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1, carInfo.y*(LEN / DPI)+1+1, 1);
  }else{
    OLED_writeDPI(carInfo.x*(LEN / DPI)+1-1, carInfo.y*(LEN / DPI)+1, 1);
  }
}

void flash_OLED_ir(char x, char y){
  for(char i=0; i<3; i++) OLED_writeDPI(x, y-1-i, irR1);
  for(char i=0; i<3; i++) OLED_writeDPI(x-1-i, y-1-i, irR2);
  for(char i=0; i<3; i++) OLED_writeDPI(x-1-i, y, irR3);
  for(char i=0; i<3; i++) OLED_writeDPI(x+1+i, y-1-i, irR4);
  for(char i=0; i<3; i++) OLED_writeDPI(x+1+i, y, irR5);
}