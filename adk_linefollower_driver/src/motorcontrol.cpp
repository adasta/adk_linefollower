/*
 * motorcontrol.cpp
 *
 *  Created on: Feb 4, 2009
 *      Author: Asher
 */
#include "motorcontrol.h"
#include <avr/io.h>
#include "pwm.h"


#define motor1DirectionPort PORTD
#define motor1DirectionPin	PIN7
#define motor1DirectionRegister DDRD

#define motor1EnablePort PORTB
#define motor1EnablePin PIN3
#define motor1EnableRegister DDRB


#define motor2DirectionPort PORTB
#define motor2DirectionPin PIN0
#define motor2DirectionRegister DDRB

#define motor2EnablePort PORTB
#define motor2EnablePin PIN4
#define motor2EnableRegister DDRB




void initMotor1(void)
{
	motor1DirectionRegister |= _BV(motor1DirectionPin) ;
	motor1EnableRegister |=  _BV(motor1EnablePin);

	motor1DirectionPort |=  _BV(motor1DirectionPin);
	motor1EnablePort |=  _BV(motor1EnablePin);
	initPWM();
}

void motor1Forward(int speed)
{
	motor1DirectionPort &= ~ _BV(motor1DirectionPin);
	invertPWM1();
	dutyCyclePWM1(speed);
}

void motor1Reverse(int speed)
{
	motor1DirectionPort |=  _BV(motor1DirectionPin);
	nonInvertPWM1();
	dutyCyclePWM1(speed);
}

void initMotor2 (void)
{
	motor2DirectionRegister |= _BV(motor2DirectionPin) | _BV(motor2EnablePin);
	motor2DirectionPort |=  _BV(motor2DirectionPin) | _BV(motor2EnablePin);
	initPWM();
}

void motor2Forward(int speed)
{
	motor2DirectionPort &= ~ _BV(motor2DirectionPin);
	invertPWM2();
	dutyCyclePWM2(speed);
}

void motor2Reverse(int speed)
{
	motor2DirectionPort |=  _BV(motor2DirectionPin);
	nonInvertPWM2();
	dutyCyclePWM2(speed);
}

void motor1SetSpeed(int speed)
{
	speed = limitSpeedMax(speed);

	//if ((speed <2) && (speed> -2))	motor1Forward(0);  // Break by putting both H-Bridge sides High
	if (speed >= 0) motor1Forward(speed);
	if (speed < 0)  motor1Reverse(-speed);
}

void motor2SetSpeed(int speed)
{
	speed = limitSpeedMax(speed);

	// if ((speed<1) && (speed> -1))	motor2Forward(0);  // Break by putting both H-Bridge sides High
	   if (speed >=0) motor2Forward(speed);
	   if (speed <0) motor2Reverse(-speed);
}

int limitSpeedMax(int speed)
{
	if (speed > 510) return 510;  // max duty cycle is 510
	if (speed < -510) return -510; // max duty cycle is 510
	return speed;
}
