/*
 * VirtualDigitalInput.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef VIRTUALDIGITALINPUT_H_
#define VIRTUALDIGITALINPUT_H_

#include <DigitalPin.h>

class VirtualDigitalInput: public DigitalPin {
public:
	VirtualDigitalInput();
	virtual ~VirtualDigitalInput();
	boolean read();
	void write(boolean value);
	void init();
private:
	boolean pinValue;
};

#endif /* VIRTUALDIGITALINPUT_H_ */
