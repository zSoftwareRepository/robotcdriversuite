#pragma config(Sensor, S1,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-accelerometer-SMUX-test1.c $
 */

/**
 * hitechnic-accelerometer.h provides an API for the HiTechnic Acceleration Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Make use of new API calls
 * - 0.3: Better comments
 * - 0.4: Fixed line number in display functionality
 * - 0.5: Now uses HTSMUX driver which has been split from common.h\n
 *        HTSMUX initialisation and scanning functions have been removed\n
 *        Removed single axis functions, they're no longer in the driver
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 * - Chris Shepherd for pointing a silly bug in the display functionality
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 20 February 2011
 * version 0.5
 */

#include "hitechnic-sensormux.h"
#include "hitechnic-accelerometer.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor HTAC = msensor_S1_1;

task main () {
  int _x_axis = 0;
  int _y_axis = 0;
  int _z_axis = 0;

  string _tmp;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Accel");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and Accel to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);

  PlaySound(soundBeepBeep);
  while(bSoundActive) EndTimeSlice();

  eraseDisplay();
  while (true) {
    // Read all of the axes at once
    if (!HTACreadAllAxes(HTAC, _x_axis, _y_axis, _z_axis)) {
      nxtDisplayTextLine(4, "ERROR!!");
      wait1Msec(2000);
      StopAllTasks();
    }

    nxtDisplayTextLine(0,"HTAC Test 1");

    // We can't provide more than 2 parameters to nxtDisplayTextLine(),
    // so we'll do in two steps using StringFormat()
    nxtDisplayTextLine(2, "   X    Y    Z");
    StringFormat(_tmp, "%4d %4d", _x_axis, _y_axis);
    nxtDisplayTextLine(3, "%s %4d", _tmp, _z_axis);

    wait1Msec(100);
  }
}

/*
 * $Id: hitechnic-accelerometer-SMUX-test1.c $
 */
