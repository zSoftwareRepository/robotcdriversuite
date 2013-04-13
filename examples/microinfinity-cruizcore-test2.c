#pragma config(Sensor, S1,     MICC,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: microinfinity-cruizcore-test2.c $
 */

/**
 * microinfinity-cruizcore.h provides an API for the MicroInfinity CruizCore XG1300L sensor.
 * This program demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to MicroInfinity for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 29 May 2011
 * version 0.1
 */

#include "microinfinity-cruizcore.h"

int angleI = 0;
int rotI = 0;
int x_accel = 0;
int y_accel = 0;
int z_accel = 0;

task updateHUD () {
  int x = 0;
  int y = 0;

  while (true) {
    nxtEraseRect(4,50, 44,10);
    nxtDisplayTextLine(2, "        H: %3d", angleI/100);
    nxtDisplayTextLine(3, "        X: %3d", x_accel/100);
    nxtDisplayTextLine(4, "        Y: %3d", y_accel/100);
    nxtDisplayTextLine(5, "        Z: %3d", z_accel/100);
    nxtDrawCircle(84, 50, 4);

    nxtDrawCircle(4, 50, 40);
    x = (cosDegrees(-1 * (angleI/100 - 90)) * 20) + 24;
    y = (sinDegrees(-1 * (angleI/100 - 90)) * 20) + 30;
    nxtDrawLine(24, 30, x, y);
    nxtEraseRect(0,0, 99, 8);
    nxtDrawRect(0,0, 99, 8);
    nxtFillRect(50,0, (float)(rotI / 150)/100.0 *50 + 50, 8);
    wait1Msec(100);
  }
}

task main () {

  nxtDisplayCenteredTextLine(0, "MicroInfinity");
  nxtDisplayTextLine(1, "CruizCore XG1300L");
  nxtDisplayCenteredTextLine(3, "Test 2");
  wait1Msec(2000);
  eraseDisplay();

  // There are 3 ranges the Cruizcore XG1300L can measure in
  // up to 2G
  // up to 4G
  // up to 8G
  MICCsetRange8G(MICC);

  // Make sure you always reset the sensor at the beginning of your program
  // The robot needs to be completely stationary or your heading and gyro
  // data won't be accurate.
  MICCreset(MICC);

  // Start the task for displaying all the sensor data.
  StartTask(updateHUD);

  nxtDisplayTextLine(0, "CruizCore XG1300L");
  while (true) {
    // Read the relative heading from the sensor.
    angleI = MICCreadRelativeHeading(MICC);

    // Read the rate of turn
    rotI = MICCreadTurnRate(MICC);

    // Read the acceleration data from the sensor
    if (!MICCreadAccel(MICC, x_accel, y_accel, z_accel)) {
      StopTask(updateHUD);
      wait1Msec(100);
      eraseDisplay();
      nxtDisplayTextLine(4, "ERROR!!");
      wait1Msec(2000);
      StopAllTasks();
    }
    wait1Msec(50);
  }
}

/*
 * $Id: microinfinity-cruizcore-test2.c $
 */
