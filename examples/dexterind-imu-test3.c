#pragma config(Sensor, S1,     DIMU,           sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: dexterind-imu-test3.c $
 */

/**
 * Warning: This code completely doesn't work if the sensor is configured while moving or tilted.
 * This code uses various laws and equations of physics to determine the direction downward is.
 * Downward is pretty vague, what it means for our purposes is the arbitrary source of acceleration.
 * When at rest, downward is toward the center of the earth, and when moving, the arrow is slightly
 * pointed towards the direction of the point it is accelerating away from.
 *
 * The dIMU should be placed on the right side of the nxt, the LED pointing rightward, and the
 * sensor's port pointing to the bottom of the NXT, connected to port 1.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Avery Radmacher for writing the original code and letting me include it with the Suite!
 * - A shout out to his parents for giving him cool toys like the LEGO MINDSTORMS NXT
 * - Big thanks to Dexter Industries for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Written by Avery Radmacher (Coder A on the ROBOTC Forums)
 * Modified by Xander Soldaat (xander_at_botbench.com)
 * 13 February 2013
 * version 0.1
 */

#include "dexterind-imu.h"

// z_val and x_val are the accel values on the Z and X axes.
// Gforce is the total force felt along both axes.
// pXrads and pZrads are arrays holding both possible values
// for the tilt of each axis.
float z_val;
float x_val;
float Gforce;
float pXrads[2];
float pZrads[2];


/**
 * Find the x tilt and z tilt that match up and returns that value.
 * Since a computer may not store exact values, or the sensor could give an
 * imperfect reading, the second block of code runs if no exact match is found.
 * If no match is still found, it returns zero radians.
 * @return matched tilt value or 0 if no match is found
 */
float match()
{
   if (pXrads[0] == pZrads[0])                 return pXrads[0];
   else if (pXrads[0] == pZrads[1])            return pXrads[0];
   else if (pXrads[1] == pZrads[0])            return pXrads[1];
   else if (pXrads[1] == pZrads[1])            return pXrads[1];
   else if (abs(pXrads[0] - pZrads[0]) < 0.01) return pXrads[0];
   else if (abs(pXrads[0] - pZrads[1]) < 0.01) return pXrads[0];
   else if (abs(pXrads[1] - pZrads[0]) < 0.01) return pXrads[1];
   else if (abs(pXrads[1] - pZrads[1]) < 0.01) return pXrads[1];
   else                                        return 0;
}


/**
 * This displays an arrow on the screen pointing downwards.
 * @param degreesFromDown the number of degrees from down
 */
void displayArrow(int degreesFromDown)
{
   eraseDisplay();
   // Otherwise, the arrow would point up.
   degreesFromDown = degreesFromDown-180;

   //If you don't know trigonometry, you can ignore this part
   nxtDrawLine(49,
               31,
               (cosDegrees(degreesFromDown     ) * 20) + 49,
               (sinDegrees(degreesFromDown     ) * 20) + 31);
   nxtDrawLine((cosDegrees(degreesFromDown - 20) * 15) + 49,
               (sinDegrees(degreesFromDown - 20) * 15) + 31,
               (cosDegrees(degreesFromDown     ) * 20) + 49,
               (sinDegrees(degreesFromDown     ) * 20) + 31);
   nxtDrawLine((cosDegrees(degreesFromDown + 20) * 15) + 49,
               (sinDegrees(degreesFromDown + 20) * 15) + 31,
               (cosDegrees(degreesFromDown     ) * 20) + 49,
               (sinDegrees(degreesFromDown     ) * 20) + 31);
}


/**
 * Normalises values to make them positive.
 */
void normalize()
{
   if (pXrads[0] < 0)
      pXrads[0] = pXrads[0] + (2 * PI);
   if (pXrads[1] < 0)
      pXrads[1] = pXrads[1] + (2 * PI);
   if (pZrads[0] < 0)
      pZrads[0] = pZrads[0] + (2 * PI);
   if (pZrads[1] < 0)
      pZrads[1] = pZrads[1] + (2 * PI);
}


/**
 * The main task
 */
task main(){

  nxtDisplayCenteredTextLine(0, "Dexter Ind.");
  nxtDisplayCenteredBigTextLine(1, "IMU");
  nxtDisplayCenteredTextLine(3, "Test 3");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);
  eraseDisplay();

  // If configuration fails, the program ends.
  if (!DIMUconfigAccel(DIMU, DIMU_ACC_RANGE_2G))
  {
		PlaySound(soundException);
		while(bSoundActive){}
		StopAllTasks();
  }

  while(nNxtButtonPressed == kNoButton)
  {
		z_val = DIMUreadAccelZAxis10Bit(DIMU);
		x_val = DIMUreadAccelXAxis10Bit(DIMU);

		// Since the axes are constantly 90 degrees apart, we can use the sum of forces law,
		// which looks like the pythagorean theorem, to discover the total force along both axes.
		Gforce = sqrt(pow(z_val, 2) + pow(x_val, 2));

		// Then we divide both values received by the total force to get numbers on the interval [-1,1].
		// This way we can input them into the arcsine and arccosine functions.
		z_val = z_val/Gforce;
		x_val = x_val/Gforce;

		pXrads[0] = asin(x_val);
		pXrads[1] = PI-pXrads[0]; //other possible X tilt value.
		pZrads[0] = acos(z_val);
		pZrads[1] = -1*pZrads[0]; //other possible Z tilt value.

		normalize();
		displayArrow(radiansToDegrees(match()));

		// This stops the screen from flashing.
		wait1Msec(100);
  }
}


/*
 * $Id: dexterind-imu-test3.c $
 */
