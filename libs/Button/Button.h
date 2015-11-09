/*
 * Button.h
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"

class Button {
public:
	Button(int pinNr, boolean logicLevel);
	virtual ~Button();
	void init();
	void initWithInternalPullup();

	boolean getValue();
	void checkButton();
	virtual void buttonPressed();
	virtual void buttonReleased();

private:

	int pin;
	boolean isActiveLow;
	boolean state;
};

#endif /* BUTTON_H_ */
