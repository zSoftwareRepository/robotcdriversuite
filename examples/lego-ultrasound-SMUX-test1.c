#pragma config(Sensor, S1,     HTSMUX,              sensorLowSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * lego-ultrasound.h provides an API for the Lego US sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 25 November 2009
 * version 0.2
 */

#include "hitechnic-sensormux.h"
#include "lego-ultrasound.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor LEGOUS = msensor_S1_1;

task main () {
  short dist = 0;

  displayCenteredTextLine(0, "Lego");
  displayCenteredBigTextLine(1, "US");
  displayCenteredTextLine(3, "SMUX Test");
  displayCenteredTextLine(5, "Connect SMUX to");
  displayCenteredTextLine(6, "S1 and US sensor");
  displayCenteredTextLine(7, "to SMUX Port 1");
  sleep(2000);

  eraseDisplay();
  displayTextLine(0, "Lego US Sensor");

  while(true) {
    // Read the current distance detected.
    dist = USreadDist(LEGOUS);

    // display the info from the sensor
    displayTextLine(3, "Dist:  %3d cm", dist);
    sleep(50);
  }
}
