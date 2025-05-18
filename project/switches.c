#include <msp430.h>
#include "stateMachine.h"
#include "switches.h"
//#include "buzzer.h"
#include "platform.h"

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES);   // If switch up, sense down
  P2IES &= (p2val | ~SWITCHES);  // If switch down, sense up

  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;   // Enables resistors for switches
  P2IE  |= SWITCHES;   // Enables interrupts from switches
  P2OUT |= SWITCHES;   // Pull-ups for switches
  P2DIR &= ~SWITCHES;  // Set switches' buts for input
  switch_update_interrupt_sense();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  if (~p2val & SW1) {
    state = MENU;
  }

  if (~p2val & SW2) {
    state = GAME;
  }

  if (~p2val & SW3 && (state == GAME)) {
    direction = 0;
    move_left();
    
  } else if (~p2val & SW4 && (state == GAME)) {
    direction = 1;
    move_right();
    
  } else {
    direction = 2;
  }
   
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

