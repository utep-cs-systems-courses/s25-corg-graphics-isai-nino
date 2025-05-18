#include <msp430.h>
#include <stdlib.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "buzzer.h"
#include "bricks.h"
#include "stateMachine.h"

int score = 0;

Brick bricks[5][8];

void bricks_init(){
  score = 0;
  int row = 30;
  
  for (int i = 0; i < 5; i++) {
    int col = 0;
    for (int j = 0; j < 8; j++) {
      bricks[i][j].col = col;
      bricks[i][j].row = row;
      bricks[i][j].status = 1;

      col += 16;
    }
    row += 12;
  }
}


void draw_bricks() {
  
  int col = 0, row = 30;

  fillRectangle(col, row, 128, 10, COLOR_RED);
  fillRectangle(col, row+12, 128, 10, COLOR_ORANGE_RED);
  fillRectangle(col, row+24, 128, 10, COLOR_YELLOW);
  fillRectangle(col, row+36, 128, 10, COLOR_GREEN);
  fillRectangle(col, row+48, 128, 10, COLOR_BLUE);
}

void check_bounce_direction(char brickCol, char brickRow) {
  // Center of ball
  int ballCenterX = ballCol + ball_size / 2;
  int ballCenterY = ballRow + ball_size / 2;

  // Center of brick
  int brickCenterX = brickCol + 8;
  int brickCenterY = brickRow + 5;

  int dx = ballCenterX - brickCenterX;
  int dy = ballCenterY - brickCenterY;


  // Determine in which axis the collision was stronger
  if (abs(dx) > abs(dy)) {
    colDirection = !colDirection;  // left/right
  } else {
    rowDirection = !rowDirection;  // up/down
  }
}


void check_brick_collision() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 8; j++) {
      if (bricks[i][j].status) {
	char brickCol = bricks[i][j].col;
	char brickRow = bricks[i][j].row;
	
	if (ballCol < brickCol+16 &&         // left
	    ballCol+ball_size > brickCol &&  // right
	    ballRow < brickRow+10 &&         // bottom  
	    ballRow+ball_size > brickRow) {  // top

	  // Collision
	  bricks[i][j].status = 0;
	  score++;
	  if (score == 40)
	    state = WIN;
	  check_bounce_direction(brickCol, brickRow);
	  play_bip();
	  fillRectangle(brickCol, brickRow, 16, 10, COLOR_BLACK);
	}
      }
    }
  }
}
