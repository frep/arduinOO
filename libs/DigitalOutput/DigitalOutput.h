/*
 * DigitalOutput.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef DIGITALOUTPUT_H_
#define DIGITALOUTPUT_H_

#include <DigitalPin.h>

class DigitalOutput: public DigitalPin {
public:
	DigitalOutput(int pin);
	virtual ~DigitalOutput();
	boolean read();
	void write(boolean value);
	void init();
private:
	int pinNr;
};

#endif /* DIGITALOUTPUT_H_ */
