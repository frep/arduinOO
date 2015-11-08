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
	led->init();
}

void ButtonIndicator::loop(){

}

