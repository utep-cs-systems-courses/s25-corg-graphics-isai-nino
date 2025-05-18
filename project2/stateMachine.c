#include <msp430.h>
#include "stateMachine.h"
#include "buzzer.h"
#include "switches.h"
#include "ball.h"
#include "bricks.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "platform.h"

State state = MENU;

static char menu = 0;
static char game = 0;
static char song = 1; // 1 : Music will play, 0 : Music will stop
static char lose = 0;
static char win = 0;

void state_machine_update()
{
    
  switch (state) {
  case MENU:
    game = 0; 
    song = 1; 
    lose = 0;
    
    // Start MENU defaults
    if (!menu) {
      menuScreen();
      titleSong();
      song = 0; 
      menu = 1;
    }
    
    break;
    
  case GAME:
    menu = 0;
    lose = 0;
    
    // Start GAME defaults
    if (!game) {
      reset_ball_position();
      gameScreen();
      bricks_init();
      game = 1;
    }

    switch_interrupt_handler();
    update_ball_direction();
    check_brick_collision();
    redraw_ball();
    update_plat();
    break;
    
  case WIN:
    song = 1;
    game = 0;
    
    if (!win) {
      winScreen();
      win = 1;
      titleSong();
      song = 0;
    }
    break;
    
  case LOSE:
    song = 1;
    game = 0;
    
    if (!lose) {
      loseScreen();
      lose = 1;
      loseSong();
      song = 0;
    }
    
    break;
  }
  
}


void menuScreen() {
  clearScreen(COLOR_GOLD);
  
  drawString5x7(43, 60, "BREAKOUT",COLOR_BLACK, COLOR_GOLD);
  drawString5x7(17, (screenHeight/2)+10, "MENU - button (1)",COLOR_BLACK, COLOR_GOLD);
  drawString5x7(17, (screenHeight/2)+23, "PLAY - button (2)",COLOR_BLACK, COLOR_GOLD);
  drawString5x7(17, (screenHeight/2)+36, "LEFT - button (3)",COLOR_BLACK, COLOR_GOLD);
  drawString5x7(17, (screenHeight/2)+49, "LEFT - button (4)",COLOR_BLACK, COLOR_GOLD);
}

void gameScreen() {
  clearScreen(COLOR_BLACK);
  fillRectangle(0,0,screenWidth,10,COLOR_WHITE);
  drawString5x7(3,1,"score:",COLOR_BLACK, COLOR_WHITE);
  drawString5x7(39,2,"32",COLOR_BLACK, COLOR_WHITE);
  draw_bricks();
}

void loseScreen() {
  fillRectangle(40,70,50,30,COLOR_RED);
  drawString5x7(42,80,"You lose",COLOR_BLACK,COLOR_RED);
}

void winScreen() {
  fillRectangle(40,70,50,30,COLOR_SKY_BLUE);
  drawString5x7(42,80,"You win",COLOR_BLACK,COLOR_SKY_BLUE);
}

void titleSong() {
  int melody[] = { 1047, 880, 880, 44, 41, 523, 44, 698, 41, 41,
		   1047, 880, 1760, 880, 1047, 55, 65, 880, 1047,
		   880, 698, 41, 523, 41, 698, 880, 1760, 1047, 880,
		   880, 1047, 55, 988, 65, 988, 41, 988, 784, 41,
		   988, 41, 784, 784, 659, 41, 1319, 784, 62, 41,
		   659, 784, 41, 41, 41, 65, 784, 988, 880, 1047 };
  
  static int currNote = 0;

  while (song) {
    if (currNote < 59) {
    
      int freq = melody[currNote];
      buzzer_set_period(2000000 / freq);
   
      __delay_cycles(2000000);
      currNote++;
      
    } else {
      currNote = 0;
      buzzer_set_period(0);
      break;
    }
  }
  
}

void loseSong() {
  int melody[] = {1319, 880, 831, 740, 932, 784, 1109, 659, 554, 370, 294};
  
  static int currNote = 0;

  while (song) {
    if (currNote < 11) {
    
      int freq = melody[currNote];
      buzzer_set_period(2000000 / freq);
   
      __delay_cycles(2000000);
      currNote++;
      
    } else {
      currNote = 0;
      buzzer_set_period(0);
      break;
    }
  }
  
}
