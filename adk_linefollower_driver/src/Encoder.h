/*
 * Encoder.h
 *
 *  Created on: Dec 2, 2009
 *      Author: asher
 */

#ifndef ENCODER_H_
#define ENCODER_H_

class Encoder {
public:
	Encoder();
	int count();
	void adjustCount(int amount); //if you need to adjust the count for sum reason
								//(putting this in for blacklash adjustments
	void clearCount();
	void update(char channelA, char channelB);
	 ~Encoder();
private:
	 int priorA; //prior A value
	 int priorB;
	 int encoderCount;

};

#endif /* ENCODER_H_ */
