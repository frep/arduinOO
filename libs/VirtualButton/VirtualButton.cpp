/*
 * VirtualButton.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "VirtualButton.h"
#include "VirtualDigitalInput.h"

VirtualButton::VirtualButton(boolean logicLevel)
: Button(0, logicLevel)
{
	pin = new VirtualDigitalInput();
}

VirtualButton::~VirtualButton() {}

void VirtualButton::write(boolean value)
{
	pin->write(value);
}
