#ifndef state_machine_included
#define state_machine_included

typedef enum {
  MENU,
  GAME,
  WIN,
  LOSE
} State;

extern State state;

void state_machine_update();
void menuScreen();
void gameScreen();
void loseScreen(); 
void winScreen();
void titleSong();
void loseSong();

#endif
