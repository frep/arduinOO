/*
 * Led.cpp
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#include "Arduino.h"
#include "Led.h"

  Led::Led(int pinNr, boolean logicLevel)
  : pin(pinNr), ledIsOn(false), activeLow(logicLevel)
  {

  }

  Led::~Led()
  {

  }

  void Led::init()
  {
    pinMode(pin, OUTPUT);
  }

  void Led::setOn()
  {
    digitalWrite(pin, (activeLow ? LOW : HIGH));
    ledIsOn = true;
  }

  void Led::setOff()
  {
    digitalWrite(pin, (activeLow ? HIGH : LOW));
    ledIsOn = false;
  }

  void Led::toggle()
  {
    ledIsOn ? setOff() : setOn();
  }

  boolean Led::isOn()
  {
    if(ledIsOn)
    {
      return true;
    }

    return false;
  }
