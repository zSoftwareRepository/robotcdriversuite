#pragma config(Sensor, S1,     HTMMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-motormux-test1.c $
 */

#include "common.h"
#include "hitechnic-motormux.h"


task main () {
  //wait1Msec(500);
  eraseDisplay();
  HTMMUXinit();

  // Reset the encoders for each motor.
  MMotorEncoderReset(mmotor_S1_1);
  MMotorEncoderReset(mmotor_S1_2);
  MMotorEncoderReset(mmotor_S1_3);
  MMotorEncoderReset(mmotor_S1_4);
  wait1Msec(10);

  // Set the encoder targets for each motor
  MMotorEncoderTarget(mmotor_S1_1, 720);
  MMotorEncoderTarget(mmotor_S1_2, -720);
  MMotorEncoderTarget(mmotor_S1_3, 1500);
  MMotorEncoderTarget(mmotor_S1_4, -1500);

  // Motor speeds only go from 0 to 25
  MMotor(mmotor_S1_1, 13);
  MMotor(mmotor_S1_2, 13);
  MMotor(mmotor_S1_3, 25);
  MMotor(mmotor_S1_4, 25);

  // Wait for the motors to be done getting to their targets.
  while (MMotorBusy(mmotor_S1_1) || MMotorBusy(mmotor_S1_2)
        || MMotorBusy(mmotor_S1_3) || MMotorBusy(mmotor_S1_4)) { wait1Msec(1); }

  PlaySound(soundBeepBeep);
  while(bSoundActive == true) EndTimeSlice();
  wait1Msec(2000);
}

/*
 * $Id: hitechnic-motormux-test1.c $
 */
