#pragma config(Sensor, S1,     MAGICWAND,      sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-magicwand-test1.c $
 */

/**
 * mindsensors-magicwand.h provides additional functionality on top of the PCF8574 driver for
 * the Mindsensors Magic Wand. This program demonstrates how to use that API to
 * control the LEDs for fun and profit!
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Magic Wand driver originally written by Mike Partain a.k.a. Spiked3 (http://www.spiked3.com/)
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 29 July 2012
 * version 0.1
 */

#include "mindsensors-magicwand.h"

task main () {

  MSMWclearALL(MAGICWAND);

  while (true)
  {

    // Blink LED 0 5 times
    for (int i = 0; i < 5; i++)
    {
      MSMWsetLED(MAGICWAND, 0, true);
      wait1Msec(150);
      MSMWsetLED(MAGICWAND, 0, false);
      wait1Msec(50);
    }

    // Do the same as above, only use the toggle function
    // Toggle LED 4
    for (int i = 0; i < 10; i++)
    {
      MSMWtoggleLED(MAGICWAND, 4);
      wait1Msec(200);
    }

    // Flash pulse all of the LEDs quickly
    for (int i = 0; i < 3; i++)
    {
      MSMWsetALL(MAGICWAND);
      wait1Msec(50);
      MSMWclearALL(MAGICWAND);
      wait1Msec(150);
    }

    // Use a cool flash effect and clear them all
    MSMWflashAndClear(MAGICWAND, 4);

		for (int j = 1; j < 10; j++)
		{
			int r = random(7);
			MSMWsetLED(MAGICWAND, r, true);
			for (int i = 0; i < 10; i++)
			{
				MSMWtoggleLED(MAGICWAND, 4);
				wait1Msec(100);
			}
		  MSMWsetLED(MAGICWAND, r, false);
		}
    wait1Msec(500);
    MSMWclearALL(MAGICWAND);

  }


}

 /*
 * $Id: mindsensors-magicwand-test1.c $
 */
