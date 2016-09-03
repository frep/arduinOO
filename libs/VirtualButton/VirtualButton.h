/*
 * VirtualButton.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef VIRTUALBUTTON_H_
#define VIRTUALBUTTON_H_

#include <Button.h>

class VirtualButton: public Button {
public:
	VirtualButton(boolean logicLevel);
	virtual ~VirtualButton();
	void write(boolean value);
};

#endif /* VIRTUALBUTTON_H_ */
