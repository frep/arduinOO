/*
 * DigitalInput.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "DigitalInput.h"

DigitalInput::DigitalInput(int pin)
{
	pinNr = pin;
}

DigitalInput::~DigitalInput(){}

void DigitalInput::init()
{
	pinMode(pinNr, INPUT);
}

boolean DigitalInput::read()
{
	return digitalRead(pinNr);
}

void DigitalInput::write(boolean value)
{
	digitalWrite(pinNr, value);
}
