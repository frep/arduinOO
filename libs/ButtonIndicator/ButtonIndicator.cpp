/*
 * ButtonIndicator.cpp
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#include "ButtonIndicator.h"

ButtonIndicator::ButtonIndicator()
{
	led = new Led(13, activeHigh);
	button = new Button(3, activeLow);
}

ButtonIndicator::~ButtonIndicator()
{
	delete button;
	delete led;
}

void ButtonIndicator::setup()
{
	Serial.begin(115200);

	led->init();
	button->initWithInternalPullup();

    Serial.print("freeRam()=");
    Serial.println(freeRam());
}

void ButtonIndicator::loop()
{
	button->checkButton();
}

