#include <msp430.h>

int redrawScreen = 1;

void wdt_c_handler()
{
  static int sec2Count = 0;
  static int sec1Count = 0;

  if (sec2Count++ >= 125) {/* 2/sec */
    sec2Count = 0;
    current_color = (current_color+1) % NUM_SQCOLORS;
    redrawScreen = 1;
  }
  if (sec1Count++ >= 250) {/* 1/sec */
    sec1Count = 0;
    current_position = (current_position+1) % NUM_POSITIONS;
    redrawScreen = 1;
  }
}
