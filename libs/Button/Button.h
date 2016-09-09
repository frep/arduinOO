/*
 * Button.h
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"
#include <DigitalPin.h>
#include <DigitalInput.h>

template<class T>
class Button {
public:
	Button(int pinNr, boolean logicLevel)
	{
		pin = new DigitalInput(pinNr);
		isActiveLow = logicLevel;
	    state = getValue();
		objButtonPressed  = NULL;
		objButtonReleased = NULL;
		fctButtonPressed  = NULL;
		fctButtonReleased = NULL;
	}

	virtual ~Button()
	{
		delete pin;
	}

	void init()
	{
	    pin->init();
	}

	void initWithInternalPullup()
	{
	    pin->init();
	    pin->write(true);
	}

	boolean getValue()
	{
	    return pin->read();
	}

	void setValue(boolean value)
	{
		pin->write(value);
	}

	void checkButton()
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

	virtual void buttonPressed()
	{
		Serial.println("button pressed");
		if((objButtonPressed != NULL) && (fctButtonPressed != NULL))
		{
			(objButtonPressed->*fctButtonPressed)();
		}
	}

	virtual void buttonReleased()
	{
		Serial.println("button released");
		if((objButtonReleased != NULL) && (fctButtonReleased != NULL))
		{
			(objButtonReleased->*fctButtonReleased)();
		}
	}

	void attachFunctionOnButtonPressed(T* obj, void (T::*func)())
	{
		objButtonPressed = obj;
		fctButtonPressed = func;
	}

	void attachFunctionOnButtonReleased(T* obj, void (T::*func)())
	{
		objButtonReleased = obj;
		fctButtonReleased = func;
	}

	void detachFunctionOnButtonPressed()
	{
		objButtonPressed = NULL;
		fctButtonPressed = NULL;
	}

	void detachFunctionOnButtonReleased()
	{
		objButtonReleased = NULL;
		fctButtonReleased = NULL;
	}

protected:

	DigitalPin* pin;
	boolean isActiveLow;
	boolean state;

	T* objButtonPressed;
	T* objButtonReleased;
	void (T::*fctButtonPressed)();
	void (T::*fctButtonReleased)();
};

#endif /* BUTTON_H_ */
