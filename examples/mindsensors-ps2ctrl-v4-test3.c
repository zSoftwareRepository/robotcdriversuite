#pragma config(Sensor, S1,     PSPNXV4,        sensorI2CCustomFastSkipStates)
#pragma config(Sensor, S2,     LASER1,         sensorAnalogActive)
#pragma config(Sensor, S3,     LASER2,         sensorAnalogActive)
#pragma config(Motor,  motorA,          ARMS,          tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          RIGHT,         tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          LEFT,          tmotorNormal, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-ps2ctrl-v4-test3.c $
 */

/**
 * mindsensors-ps2ctrl-v4.h provides an API for the Mindsensors PS2 controller sensor
 * with referee signal receiver.  This program demonstrates how to use that API
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 02 August 2012
 * version 0.1
 */

#include "mindsensors-ps2ctrl-v4.h"

#define RAW_RIGHT   0x45B
#define RAW_LEFT    0x45A
#define RAW_FWD     0x458
#define RAW_REV     0x459
#define RAW_STOP    0x45C

#define goBotRight()  moveBot(-20, 20)
#define goBotLeft()   moveBot(20, -20)
#define goBotFwd()    moveBot(50, 50)
#define goBotRev()    moveBot(-50, -50)
#define goBotStop()   moveBot(0, 0)

void moveBot(int speedRight, int speedLeft)
{
  motor[RIGHT] = speedRight;
  motor[LEFT] = speedLeft;
}

task main ()
{
  ubyte counter = 0;
  ubyte oldCounter = 0;
  long rawValue = 0;
  long oldRawValue = 0;

  nxtDisplayCenteredTextLine(0, "Mindsensors");
  nxtDisplayCenteredBigTextLine(1, "PSP-Nx");
  nxtDisplayCenteredTextLine(3, "Test 3");
  wait1Msec(2000);

  PlaySound(soundBeepBeep);
  while(bSoundActive) EndTimeSlice();

  eraseDisplay();
  while (true)
  {
    // Get the current counter value, wraps at 255
    counter = PSPV4readRefSignalCount(PSPNXV4);

    if (oldCounter != counter)
    {
      // Raw value will also "see" commands from the remote
      // that are not recognised as "play", "stop", "forward" or "rewind".
      // You could use this to control additional aspects of your robot!
      rawValue = PSPV4readRawRefTXValue(PSPNXV4);

      if (oldRawValue != rawValue)
      {
        PlaySound(soundShortBlip);
        switch(rawValue)
        {
          case RAW_RIGHT:   nxtDisplayCenteredBigTextLine(3, "RIGHT");
                            goBotRight();
                            break;
          case RAW_LEFT:    nxtDisplayCenteredBigTextLine(3, "LEFT");
                            goBotLeft();
                            break;
          case RAW_FWD:     nxtDisplayCenteredBigTextLine(3, "FWD");
                            goBotFwd();
                            break;
          case RAW_REV:     nxtDisplayCenteredBigTextLine(3, "REV");
                            goBotRev();
                            break;
          case RAW_STOP:    nxtDisplayCenteredBigTextLine(3, "STOP");
                            goBotStop();
                            break;
        }
      }
      nxtDisplayTextLine(7, "Raw:  0x%03X", rawValue);

      // Update the counters and signals
      oldCounter = counter;
      oldRawValue = rawValue;
    }
    wait1Msec(50);
  }
}


/*
 * $Id: mindsensors-ps2ctrl-v4-test3.c $
 */
