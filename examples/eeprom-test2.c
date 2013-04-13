#pragma config(Sensor, S1,     EEPROM,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: eeprom-test2.c $
 */

/**
 * eeprom.h provides an API for the AT24C512, 24AA512 and 24AA1025 EEPROMs.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Removed common.h include\n
 *        Removed array structs, replaced with typedefs
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 20 February 2011
 * version 0.2
 */

#include "eeprom.h"

//tByteArray data;

task main () {
  tByteArray data;

  memset(data, 0, sizeof(tByteArray));
  data[0] = 22;
  EEPROMwriteBytes(EEPROM, 0, data, 1);
  // After a write, you *must* wait 5 msec
  wait1Msec(5);

  eraseDisplay();
  memset(data, 0, sizeof(tByteArray));
  EEPROMreadBytes(EEPROM, 0, data, 1);
  // Make sure the string is 0 terminated.

  nxtDisplayTextLine(1, "%d", data[0]);
  wait1Msec(2000);
}

/*
 * $Id: eeprom-test2.c $
 */
