/*
 * AD5274.h
 *
 *  Created on: 13.09.2016
 *      Author: frehnerp
 */

#ifndef AD5274_H_
#define AD5274_H_

#include <Wire.h>

class AD5274 {
public:
	AD5274(uint16_t address, uint32_t maxRes);
	virtual ~AD5274();
	void init();
	bool setResistor(uint16_t resistorValue);
	void setRDAC(uint8_t value);
	uint8_t getRDAC();
private:
	uint16_t address;
	uint32_t maxRes;
};

#endif /* AD5274_H_ */
