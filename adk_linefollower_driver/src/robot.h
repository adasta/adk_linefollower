/*
 * robot.h
 *
 *  Created on: Dec 9, 2009
 *      Author: asher
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#ifndef roboRocks
#define roboRocks

#include "Encoder.h"


#define feedBackLoopFrequency 30.5
#define EncoderPulsesPerRevolution 564
#define wheelDiameter 6.0325 //cm  (2.375 inches)
#define encoderCorrectionFactor 80/63
#define EncoderPulsePerCm (EncoderPulsesPerRevolution/(wheelDiameter*3.14) * encoderCorrectionFactor)
#define velEncoderPerCm  EncoderPulsePerCm/feedBackLoopFrequency


void RobotInit();

  struct robotState  //standard robot has ultrasound and speed controlled wheels
{		int stuff;
		struct wheel
		{
			int kpGain;  // proportional gain constant
			int kiGain; //  integral gain constant
			int kDGain; // derivative gain constant
			Encoder encoder;
			int previousCount;
			int vel;
			int velD;
			int countD; // desired distance in encoder counts
			int velCM;   // current velocity counts
			int error;
			int errorp;
			char blacklashFlag;// Use for backlash control
			int pwmPeriod;

		}  rightWheel,  leftWheel;
		char feedbackState;
} ;
extern robotState Robot;


 void initEncoders();
 void initSpeedControl();

 void setLeftMotorSpeed(int cmPerSec);
 void setRightMotorSpeed(int cmPerSec);
 void move(float cmPerSec, float distanceCM);
 void turn(float cmPerSec, int AngleDegrees);



void RobotInit();

void stop();

#endif
#endif /* ROBOT_H_ */
