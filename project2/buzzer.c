#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init(){
  timerAUpmode(); // used for buzzer
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // enable the buzzer output (P2.6)
}

void play_bip(){
  buzzer_set_period(2000);
  __delay_cycles(500000);
  buzzer_set_period(0);
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1; // one half cycle
} 
