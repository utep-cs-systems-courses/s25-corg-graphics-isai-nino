#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "buzzer.h"
#include "bricks.h"
#include "platform.h"

char platCol = 60;
char platRow = 145;
char direction;

char width = 25;
char height = 5;

/*
void set_boundaries() {
  if (platCol < 2) {
    platCol = 2;
    set_plat_color(COLOR_RED);
    
  } else if (platCol > (screenWidth - width)) {
    platCol = (screenWidth - width);
    set_plat_color(COLOR_RED);
    
  } else {
    set_plat_color(COLOR_HOT_PINK);
  }
  }*/


void move_left() {
  platCol--;
  set_boundaries_s();
  update_plat();
}


void move_right() {
  platCol++;
  set_boundaries_s();
  update_plat();
}


void erase_plat_col(char col, char row, char color) {
  char col2 = col;
  if (direction == 0)
    col2 += width;
  if (direction == 1)
    col2 -= 1;

  for (int i = 0; i < height; i++) {
    drawPixel(col2, row, color);
    row++;
  }
}


int plat_color = COLOR_HOT_PINK;

void set_plat_color(int color) {
  plat_color = color;
}

void update_plat() {
  erase_plat_col(platCol, platRow, COLOR_BLACK);
  fillRectangle(platCol, platRow, 25, 5, plat_color);
}

