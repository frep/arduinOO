/*
 * DigitalInput.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef DIGITALINPUT_H_
#define DIGITALINPUT_H_

#include <DigitalPin.h>

class DigitalInput: public DigitalPin {
public:
	DigitalInput(int pin);
	virtual ~DigitalInput();
	boolean read();
	void write(boolean value);
	void init();
private:
	int pinNr;
};

#endif /* DIGITALINPUT_H_ */
