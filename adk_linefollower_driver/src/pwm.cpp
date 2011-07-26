/*
 * pwm.c
 *
 *  Created on: Feb 4, 2009
 *      Author: Asher
 */
#include <avr/io.h>
#include "pwm.h"

// For Piper, we will be using OC4A which is for one of the motors; PH3
// For the other motor, we will be use


/*To use the PWM to control a motor with the axon, you want to use Phase correct PWM mode.
 * The following code will explain how to set up a phase correct PWM on any of the ouput compare pins.
 *
 *TCNTn (Timer/Counter) -  Actual counter used to keep track of time
 *OCRn -  OUtput compare register; set value for compare of pwm
 *ICRn -  Input Capture Register; sets top value and thus period of pwm
 *
 *For Motor Control, we are using Frequency and Phase correct pwm in Mode 8:
 *To set Mode :
 *		WGMn3: 1			of TCCRnB
 *		WGMn2: 0
 *		WGMn1: 0			of TCCRnA
 *		WGMn0: 0
 *
 *In non-inverted Mode, PWM will be cleared on match of count up, and set on match of count down
 *Set the following bits in TCCRnA to both choose which channel (A, B, or C) and inverted versus non
 *		COMn(A,B,C)0  =  		1				0
 *		COMn(A,B,C)1  = 		1				1
 *						non-inverted		inverted
 *
 *To choose timer pre-scaler, use CSn bits of TCCRnB.  For this application
 * we want no pre-scaler. So only CSn0 bit is set.
 *
 */
void initPWM(void)
{
	//initializes PWM a to non-inverted mode, 25khz, full duty cycle
	// Timer 1 using channel A and B
	ICR1 = 800; // Set TOP for 640 so that you have a pwm frequency of 20khtz
	TCCR1A =  _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11);
	TCCR1B =  _BV(WGM12)| _BV(CS10);
	OCR1A = 0;
	OCR1B = 0;
	DDRB |= _BV(PIN2) | _BV(PIN1); // Channel A is PB1 channel B is PB2
}

void invertPWM1(void)
{
	TCCR1A &= ~_BV(COM1A0);
	TCCR1A |= _BV(COM1A1);
}
void nonInvertPWM1( void)
{
	TCCR1A |= _BV(COM1A1) | _BV(COM1A0);

}


void invertPWM2(void)
{
	TCCR1A &= ~_BV(COM1B0);
	TCCR1A |= _BV(COM1B1);
}

void nonInvertPWM2( void)
{
	TCCR1A |= _BV(COM1B1) | _BV(COM1B0);
}

void dutyCyclePWM1(int dutyCycle)
{
	OCR1A = dutyCycle;
}

void dutyCyclePWM2(int dutyCycle)
{
	OCR1B= dutyCycle;
}


