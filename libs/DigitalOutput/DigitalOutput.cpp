/*
 * DigitalOutput.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "DigitalOutput.h"

DigitalOutput::DigitalOutput(int pin)
{
	pinNr = pin;
}

DigitalOutput::~DigitalOutput() {}

boolean DigitalOutput::read()
{
	return digitalRead(pinNr);
}

void DigitalOutput::write(boolean value)
{
	digitalWrite(pinNr, value);
}

void DigitalOutput::init()
{
	pinMode(pinNr, OUTPUT);
}
