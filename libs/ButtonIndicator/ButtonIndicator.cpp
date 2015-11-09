/*
 * ButtonIndicator.cpp
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#include "ButtonIndicator.h"

ButtonIndicator::ButtonIndicator() {
	led = new Led(13, false);
}

ButtonIndicator::~ButtonIndicator() {
	delete led;
}

void ButtonIndicator::setup(){
	Serial.begin(115200);
	led->init();
    Serial.print("freeRam()=");
    Serial.println(freeRam());
}

void ButtonIndicator::loop(){

}

