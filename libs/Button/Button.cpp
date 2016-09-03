/*
 * Button.cpp
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#include "Button.h"
#include "Arduino.h"
#include <DigitalInput.h>

  Button::Button(){}

  Button::Button(int pinNr, boolean logicLevel)
  : isActiveLow(logicLevel)
  {
	pin = new DigitalInput(pinNr);
    state = getValue();
  }

  Button::~Button()
  {

  }

  void Button::init()
  {
    pin->init();
  }

  void Button::initWithInternalPullup()
  {
    pin->init();
    pin->write(true);
  }

  boolean Button::getValue()
  {
    return pin->read();
  }

  void Button::checkButton()
  {
    if(state != getValue())
    {
      // Button state has changed

      if(getValue() == false)
      {
        if(isActiveLow)
        {
        	buttonPressed();
        }
        else
        {
        	buttonReleased();
        }
      }
      else
      {
        if(isActiveLow)
        {
        	buttonReleased();
        }
        else
        {
        	buttonPressed();
        }
      }
      state = getValue();
    }
  }

  void Button::buttonPressed()
  {
	  Serial.println("button pressed");
  }

  void Button::buttonReleased()
  {
	  Serial.println("button released");
  }
