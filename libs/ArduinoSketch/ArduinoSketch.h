/*
 * ArduinoSketch.h
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#ifndef ARDUINOSKETCH_H_
#define ARDUINOSKETCH_H_

#include "Arduino.h"

class ArduinoSketch
{

 public:
  static const boolean activeLow = true;
  static const boolean activeHigh = false;
  virtual ~ArduinoSketch();
  virtual void setup() = 0;
  virtual void loop() = 0;
  int freeRam();
};


#endif /* ARDUINOSKETCH_H_ */
