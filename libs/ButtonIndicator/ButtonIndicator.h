/*
 * ButtonIndicator.h
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#ifndef BUTTONINDICATOR_H_
#define BUTTONINDICATOR_H_

#include <ArduinoSketch.h>
#include <Led.h>
#include <Button.h>

class ButtonIndicator: public ArduinoSketch {
public:
	ButtonIndicator();
	virtual ~ButtonIndicator();
	virtual void setup();
	virtual void loop();
	Led* led;
	Button* button;
};

#endif /* BUTTONINDICATOR_H_ */
