/*
 * VirtualButtonEncoder.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef VIRTUALBUTTONENCODER_H_
#define VIRTUALBUTTONENCODER_H_

#include <ButtonEncoder.h>

class VirtualButtonEncoder: public ButtonEncoder {
public:
	VirtualButtonEncoder();
	virtual ~VirtualButtonEncoder();
	void setChA(boolean value);
	void setChB(boolean value);
	void setBut(boolean value);
};

#endif /* VIRTUALBUTTONENCODER_H_ */
