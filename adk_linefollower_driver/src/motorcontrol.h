/*
 * motorcontrol.h
 *
 *  Created on: Feb 4, 2009
 *      Author: Asher
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_
#include <avr/io.h>

void initMotor1 (void);
void initMotor2(void);


void motor1Forward(int speed);
void motor1Reverse(int speed);

void motor2Forward(int speed);
void motor2Reverse(int speed);

void motor1SetSpeed(int speed);
void motor2SetSpeed(int speed);

int limitSpeedMax(int speed);

#endif /* MOTORCONTROL_H_ */
