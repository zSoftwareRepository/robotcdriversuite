#pragma config(Sensor, S1,     LEGOTS,              sensorAnalogInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: lego-touch-test1.c $
 */

/**
 * LEGOLS-driver.h provides an API for the Lego Light Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 25 November 2009
 * version 0.2
 */

#include "lego-touch.h"

task main() {
  nxtDisplayCenteredTextLine(0, "Lego");
  nxtDisplayCenteredBigTextLine(1, "TOUCH");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);

  eraseDisplay();

  while (true) {
    if (TSreadState(LEGOTS))
      nxtDisplayCenteredBigTextLine(3, "ACTIVE");
    else
      nxtDisplayCenteredBigTextLine(3, "INACTIVE");
    wait1Msec(50);
  }
}

/*
 * $Id: lego-touch-test1.c $
 */
