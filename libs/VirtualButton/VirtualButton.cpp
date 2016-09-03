/*
 * VirtualButton.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "VirtualButton.h"
#include "VirtualDigitalInput.h"

VirtualButton::VirtualButton(boolean logicLevel)
{
	pin = new VirtualDigitalInput();
	isActiveLow = logicLevel;
}

VirtualButton::~VirtualButton() {
	// TODO Auto-generated destructor stub
}

void VirtualButton::write(boolean value)
{
	pin->write(value);
}
