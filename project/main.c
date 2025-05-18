#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "ball.h"
#include "buzzer.h"
#include "bricks.h"
#include "stateMachine.h"

int main()
{
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  
  clearScreen(COLOR_YELLOW);

  enableWDTInterrupts();      // Enable periodic interrupt
  or_sr(0x8);
}


int secondCount = 0;

void __interrupt_vec(WDT_VECTOR) WDT(){
  secondCount ++;
  if (secondCount >= 3) { // 250 every second
    secondCount = 0; // Reset count 

    state_machine_update();
    switch_interrupt_handler();
  }
} 
