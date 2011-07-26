/*
 * pwm.h
 *
 *  Created on: Feb 4, 2009
 *      Author: Asher
 */

#ifndef PWM_H_
#define PWM_H_

//PWM1 is on OC4A
//PWM2 is on OC2B

//Frequency is 25k
//Initially set to hold PWM Pin high

void initPWM(void);
void invertPWM1(void);
void nonInvertPWM1( void);


void invertPWM2(void);

void nonInvertPWM2( void);

void dutyCyclePWM1(int dutyCycle);

void dutyCyclePWM2(int dutyCycle);


#endif /* PWM_H_ */
