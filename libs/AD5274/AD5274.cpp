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
	Wire.beginTransmission(address);
	Wire.write(0x1c);
	Wire.write(0x02);
	Wire.endTransmission();
}

bool AD5274::setResistor(uint16_t resistorValue)
{
	if(resistorValue <= maxRes)
	{
		uint8_t rdacValue = (uint8_t)(resistorValue*256/maxRes);
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
	//Serial.print("send value: ");
	//Serial.print(value);
	//Serial.println(" to digPot");
	uint16_t regValue = 0x0400 | (value << 2);
	//Serial.print("RegValue: 0x");
	//Serial.println(regValue, HEX);
	byte val1 = (byte)(regValue >> 8);
	byte val2 = (byte)((regValue << 8) >> 8);
	//Serial.print("Send 0x");
	//Serial.print(val1, HEX);
	//Serial.print(val2, HEX);
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

	//int bytes = Wire.available();
	//Serial.print(bytes);
	//Serial.println(" bytes on Wire available: ");

	byte val1 = Wire.read();
	byte val2 = Wire.read();
	uint16_t regValue = (val1 << 8) | val2;

	//Serial.print("val1: 0x");
	//Serial.println(val1, HEX);
	//Serial.print("val2: 0x");
	//Serial.println(val2, HEX);
	//Serial.print("regValue: 0x");
	//Serial.println(regValue, HEX);

	return (uint8_t)((regValue << 6) >> 8);
}
