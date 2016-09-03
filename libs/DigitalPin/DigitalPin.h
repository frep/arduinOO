/*
 * DigitalPin.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef DIGITALPIN_H_
#define DIGITALPIN_H_

#include "Arduino.h"

class DigitalPin
{
public:
	virtual ~DigitalPin(){};
	virtual boolean read() = 0;
	virtual void write(boolean value) = 0;
	virtual void init() = 0;
	static const boolean high = true;
	static const boolean low = false;
};

#endif /* DIGITALPIN_H_ */
