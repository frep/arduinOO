/*
 * VirtualButton.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef VIRTUALBUTTON_H_
#define VIRTUALBUTTON_H_

#include <Button.h>
#include "VirtualDigitalInput.h"

template<class T>
class VirtualButton: public Button<T>
{
public:
	VirtualButton(boolean logicLevel)
	: Button<T>(0, logicLevel)
	{
		Button<T>::pin = new VirtualDigitalInput();
	}

	virtual ~VirtualButton()
	{
		delete Button<T>::pin;
	}

	void write(boolean value)
	{
		Button<T>::pin->write(value);
	}
};

#endif /* VIRTUALBUTTON_H_ */
