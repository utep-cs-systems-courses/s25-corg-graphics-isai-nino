
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

// Starting position of shape
int row = screenHeight/2, col = screenWidth/2;

int shape_size = 1;

int colDirection = 1; // right = 0, left = 1
int rowDirection = 1; // up = 0, down = 1

int main()
{
  configureClocks();
  lcd_init();
  
  clearScreen(COLOR_YELLOW);
  
  enableWDTInterrupts();      // Enable periodic interrupt
  or_sr(0x8);
}

void direction_setting() {

  // Setting width boundaries
  if (col == (screenWidth - shape_size))
    colDirection = 0;

  if (col == 1)
    colDirection = 1;

  // Setting height boundaries
  if (row == (screenHeight - shape_size))
    rowDirection = 0;

  if (row == 1)
    rowDirection = 1;

  /*
    colDirection & rowDirection are boolean variable to set 
    the direction to which the shape is being drawn
    
    colDirection: 0 == left and 1 == right
    rowDirection: 0 == up and 1 == down

  */
  colDirection == 1 ? col++ : col--;
  rowDirection == 1 ? row++ : row--;
}

// Erases the previous or next col of a shape

void eraseCol(int col, int row, int color, int size, int direction) {
  int row2 = row;

  for (int i = 0; i <= size; i++) {
    if (direction)
      drawPixel(col+size, row2, color);

    else
      drawPixel(col-1, row2, color);

    row2++;
  }
}

// Erases the previous or next row of a shape

void eraseRow(int col, int row, int color, int size, int direction) {
  int col2 = col-1;
  
  for (int i = 0; i <= size+1; i++) {
    if (direction)
      drawPixel(col2, row+size, color);

    else
      drawPixel(col2, row-1, color);

    col2++;
  }
}

void redrawScreen() {
  eraseCol(col, row, COLOR_BLACK, shape_size, !colDirection);
  eraseRow(col, row, COLOR_BLACK, shape_size, !rowDirection);
  
  fillRectangle(col, row, shape_size, shape_size, COLOR_BLUE);
}

int secondCount = 0;
void __interrupt_vec(WDT_VECTOR) WDT(){
  secondCount ++;
  if (secondCount >= 1) { /* once each sec... */
    secondCount = 0;/* reset count */

    direction_setting();
    redrawScreen();
  }
} 
