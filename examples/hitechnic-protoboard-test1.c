#pragma config(Sensor, S1,     HTPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-protoboard-test1.c $
 */

/**
 * hitechnic-protoboard.h provides an API for the HiTechnic Protoboard.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 25 November 2009
 * version 0.2
 */

#include "hitechnic-protoboard.h"

task main() {
  int _chVal = 0;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Proto");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect HTPB");
  nxtDisplayCenteredTextLine(6, "to S1");

  wait1Msec(2000);
  // Setup all the digital IO ports as outputs (0xFF)
  if (!HTPBsetupIO(HTPB, 0xFF)) {
    nxtDisplayTextLine(4, "ERROR!!");
    wait1Msec(2000);
    StopAllTasks();
  }

  while(true) {
    eraseDisplay();
    // get the value for ADC channel 0, we want a 10 bit answer
    _chVal = HTPBreadADC(HTPB, 0, 10);
    nxtDisplayTextLine(4, "A0: %d", _chVal);

    // if _chVal is more than 512, turn on the LED, otherwise turn it off.
    if (_chVal > 512) {
      if (!HTPBwriteIO(HTPB, 0xFF)) nxtDisplayTextLine(5, "ERR WRITE");
    } else {
      if (!HTPBwriteIO(HTPB, 0x00)) nxtDisplayTextLine(5, "ERR WRITE");
    }
    wait1Msec(100);
  }
}

/*
 * $Id: hitechnic-protoboard-test1.c $
 */
