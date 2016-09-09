/*
 * VirtualButtonEncoder.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef VIRTUALBUTTONENCODER_H_
#define VIRTUALBUTTONENCODER_H_

#include <ButtonEncoder.h>
#include <VirtualDigitalInput.h>
#include <VirtualButton.h>

template<class T>
class VirtualButtonEncoder: public ButtonEncoder<T> {
public:
	VirtualButtonEncoder()
	: ButtonEncoder<T>(0, 0, 0)
	{
		ButtonEncoder<T>::chaPin = new VirtualDigitalInput();
		ButtonEncoder<T>::chbPin = new VirtualDigitalInput();
		ButtonEncoder<T>::butPin = new VirtualButton<T>(true);
	}

	virtual ~VirtualButtonEncoder()
	{
		delete ButtonEncoder<T>::chaPin;
		delete ButtonEncoder<T>::chbPin;
		delete ButtonEncoder<T>::butPin;
	}

	void setChA(boolean value)
	{
		ButtonEncoder<T>::chaPin->write(value);
	}

	void setChB(boolean value)
	{
		ButtonEncoder<T>::chbPin->write(value);
	}

	void setBut(boolean value)
	{
		ButtonEncoder<T>::butPin->setValue(value);
	}
};

#endif /* VIRTUALBUTTONENCODER_H_ */
