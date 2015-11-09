/*
 * Button.cpp
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#include "Button.h"
#include "Arduino.h"

  Button::Button(int pinNr, boolean logicLevel)
  : pin(pinNr), isActiveLow(logicLevel)
  {
    state = getValue();
  }

  Button::~Button()
  {

  }

  void Button::init()
  {
    pinMode(pin, INPUT);
  }

  void Button::initWithInternalPullup()
  {
    pinMode(pin, INPUT_PULLUP);
  }

  boolean Button::getValue()
  {
    return digitalRead(pin);
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
