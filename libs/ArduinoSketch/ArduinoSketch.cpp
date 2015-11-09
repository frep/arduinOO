/*
 * ArduinoSketch.cpp
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#include "ArduinoSketch.h"

ArduinoSketch::~ArduinoSketch()
{
}

int ArduinoSketch::freeRam()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
