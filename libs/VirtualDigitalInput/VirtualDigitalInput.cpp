/*
 * VirtualDigitalInput.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "VirtualDigitalInput.h"

VirtualDigitalInput::VirtualDigitalInput()
{
	pinValue = false;
}

VirtualDigitalInput::~VirtualDigitalInput() {}

boolean VirtualDigitalInput::read()
{
	return pinValue;
}

void VirtualDigitalInput::write(boolean value)
{
	pinValue = value;
}

void VirtualDigitalInput::init()
{

}
