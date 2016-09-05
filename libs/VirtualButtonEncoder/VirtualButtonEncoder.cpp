/*
 * VirtualButtonEncoder.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "VirtualButtonEncoder.h"
#include <VirtualDigitalInput.h>
#include <VirtualButton.h>

VirtualButtonEncoder::VirtualButtonEncoder()
: ButtonEncoder(0, 0, 0)
{
	chaPin = new VirtualDigitalInput();
	chbPin = new VirtualDigitalInput();
	butPin = new VirtualButton(true);
}

VirtualButtonEncoder::~VirtualButtonEncoder()
{
	delete chaPin;
	delete chbPin;
	delete butPin;
}

void VirtualButtonEncoder::setChA(boolean value)
{
	chaPin->write(value);
}

void VirtualButtonEncoder::setChB(boolean value)
{
	chbPin->write(value);
}

void VirtualButtonEncoder::setBut(boolean value)
{
	butPin->setValue(value);
}
