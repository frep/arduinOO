/*
 * AD5274.cpp
 *
 *  Created on: 13.09.2016
 *      Author: frehnerp
 */

#include "AD5274.h"
#include "Arduino.h"

AD5274::AD5274(uint16_t address, uint32_t maxRes)
: address(address), maxRes(maxRes)
{
}

AD5274::~AD5274(){}

void AD5274::init()
{
	// enable rdac register changes over i2c
	Wire.beginTransmission(address);
	Wire.write(0x1c);
	Wire.write(0x02);
	Wire.endTransmission();
}

bool AD5274::setResistor(uint32_t resistorValue)
{
	if(resistorValue <= maxRes)
	{
		uint8_t rdacValue = (uint8_t)(resistorValue*255/maxRes);
		setRDAC(rdacValue);
		Serial.print("resistor value: ");
		Serial.print(resistorValue);
		Serial.print(" corresponds to rdac = ");
		Serial.println(rdacValue);
		return true;
	}
	else
	{
		return false;
	}
}

void AD5274::setRDAC(uint8_t value)
{
	uint16_t regValue = 0x0400 | (value << 2);
	byte val1 = (byte)(regValue >> 8);
	byte val2 = (byte)((regValue << 8) >> 8);
	Wire.beginTransmission(address);
	Wire.write(val1);
	Wire.write(val2);
	Wire.endTransmission();
}

uint8_t AD5274::getRDAC()
{
	// empty buffer
	while(Wire.available())
	{
		  byte c = Wire.read();  // receive a byte as character
		  Serial.print("0x");
		  Serial.print(c, HEX);  // print the character
		  Serial.print(" ");
	}
	// Send read command
	Wire.beginTransmission(address);
	Wire.write(0x08);
	Wire.write(0x00);
	Wire.endTransmission();

	Wire.requestFrom(address, 2);

	byte val1 = Wire.read();
	byte val2 = Wire.read();
	uint16_t regValue = (val1 << 8) | val2;

	return (uint8_t)((regValue << 6) >> 8);
}
