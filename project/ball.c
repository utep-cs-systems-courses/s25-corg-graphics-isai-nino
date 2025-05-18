#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "buzzer.h"
#include "platform.h"
#include "stateMachine.h"

// Ball parameters
char ball_size = 5;
char ballRow = 130;
char ballCol = screenWidth/2;

char colDirection = 1; // left= 0, right = 1
char rowDirection = 0; // up = 0, down = 1


void reset_ball_position() {
  ballRow = 130;
  ballCol = screenWidth/2;
  colDirection = 1;
  rowDirection = 0;
}


void update_ball_direction() {

  // Setting width boundaries
  if (ballCol == (screenWidth - ball_size)){
    play_bip();
    colDirection = 0; // left
  }
  
  if (ballCol == 1) {
    play_bip();
    colDirection = 1; // right
  }
  
  // Setting height boundaries
  if (ballRow+(ball_size/2) == (screenHeight - ball_size)){
    play_bip();
    state = LOSE;
    rowDirection = 0; // up
  }
  
  if (ballRow == 10) {
    play_bip();
    rowDirection = 1; // down
  }

  // Bouncing on the platform
  if (ballRow == (platRow - ball_size) &&
      ballCol < (platCol + width+2) &&
      ballCol > platCol-3) {
    play_bip();
    rowDirection = 0; // up
  }
    
  /*
    colDirection & rowDirection are boolean variables to set 
    the direction to which the shape is being drawn

    colDirection: 0 == left and 1 == right
    rowDirection: 0 == up and 1 == down
  */

  colDirection == 1 ? ballCol++ : ballCol--;
  rowDirection == 1 ? ballRow++ : ballRow--;
}


// Erases the previous or next col of the ball
void erase_ball_col(int col, int row, int color, int size, int direction) {
  int row2 = row;

  for (int i = 0; i <= size; i++) {
    if (direction)
      drawPixel(col+size, row2, color);

    else
      drawPixel(col-1, row2, color);

    row2++;
  }
}


// Erases the previous or next row of the ball
void erase_ball_row(int col, int row, int color, int size, int direction) {
  int col2 = col-1;

  for (int i = 0; i <= size+1; i++) {
    if (direction)
      drawPixel(col2, row+size, color);

    else
      drawPixel(col2, row-1, color);

    col2++;
  }
}


void redraw_ball() {
  erase_ball_col(ballCol, ballRow, COLOR_BLACK, ball_size, !colDirection);
  erase_ball_row(ballCol, ballRow, COLOR_BLACK, ball_size, !rowDirection);

  fillRectangle(ballCol, ballRow, ball_size, ball_size, COLOR_WHITE);
}
