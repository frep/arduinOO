/*
 * MAX5814.cpp
 *
 *  Created on: 29.11.2016
 *      Author: FREP
 */

#include "Arduino.h"
#include "MAX5814.h"
#include "Wire.h"

	// POWER MODES:
	const uint8_t MAX5814::powerMode_Normal = 0x00;
	const uint8_t MAX5814::powerMode_1kR    = 0x01;
	const uint8_t MAX5814::powerMode_100KR  = 0x02;
	const uint8_t MAX5814::powerMode_hiZ    = 0x03;

	// CONFIG MODES:
	const uint8_t MAX5814::latchOperational = 0x00;
	const uint8_t MAX5814::latchTransparent = 0x01;


MAX5814::MAX5814(uint8_t address)
: address(address)
{}

MAX5814::~MAX5814(){}

void MAX5814::codeN(uint8_t dac, uint16_t value)
{
	uint8_t byte_cmd      = 0x00 | dac;
	uint8_t byte_dataHigh = (uint8_t)(value >> 2);
	uint8_t byte_dataLow  = (uint8_t)(value << 6);
	sendCmd(byte_cmd, byte_dataHigh, byte_dataLow);
}

void MAX5814::loadN(uint8_t dac)
{
	uint8_t byte_cmd = 0x10 | dac;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::power(uint8_t dac, uint8_t powerMode)
{
	uint8_t byte_cmd = 0x40 | powerMode;
	sendCmd(byte_cmd, dac2data(dac), 0x00);
}

void MAX5814::clear()
{
	sendCmd(0x50, 0x00, 0x00);
}

void MAX5814::reset()
{
	sendCmd(0x51, 0x00, 0x00);
}

void MAX5814::config(uint8_t dac, uint8_t configMode)
{
	uint8_t byte_cmd = 0x60 | configMode;
	sendCmd(byte_cmd, dac2data(dac), 0x00);
}

void MAX5814::setRef_Ext()
{
	uint8_t byte_cmd = 0x70 | 0x00;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::setRef_2V5()
{
	uint8_t byte_cmd = 0x70 | 0x01;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::setRef_2V0()
{
	uint8_t byte_cmd = 0x70 | 0x02;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::setRef_4V1()
{
	uint8_t byte_cmd = 0x70 | 0x03;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::codeAll(uint16_t value)
{
	uint8_t byte_cmd      = 0x80;
	uint8_t byte_dataHigh = (uint8_t)(value >> 2);
	uint8_t byte_dataLow  = (uint8_t)(value << 6);
	sendCmd(byte_cmd, byte_dataHigh, byte_dataLow);
}

void MAX5814::loadAll()
{
	uint8_t byte_cmd = 0x81;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::codeAll_loadAll(uint16_t value)
{
	uint8_t byte_cmd      = 0x82;
	uint8_t byte_dataHigh = (uint8_t)(value >> 2);
	uint8_t byte_dataLow  = (uint8_t)(value << 6);
	sendCmd(byte_cmd, byte_dataHigh, byte_dataLow);
}

void MAX5814::sendCmd(uint8_t byte_cmd, uint8_t byte_dataHigh, uint8_t byte_dataLow)
{
	Wire.beginTransmission(address);
	Wire.write(byte_cmd);
	Wire.write(byte_dataHigh);
	Wire.write(byte_dataLow);
	Wire.endTransmission();
/*
	Serial.println("");
	Serial.println(byte_cmd, HEX);
	Serial.println(byte_dataHigh, HEX);
	Serial.println(byte_dataLow, HEX);
	Serial.println("");
*/
}

uint8_t MAX5814::dac2data(uint8_t dac)
{
	switch(dac)
	{
	case 0x00:
		return 0x01;
	case 0x01:
		return 0x02;
	case 0x02:
		return 0x04;
	case 0x03:
		return 0x08;
	default:
		return 0x00;
	}
	return 0x00;
}

void MAX5814::readbackCmd()
{
	Serial.println("");
	// request 3 bytes from address
	Wire.requestFrom((int)address, 3);
	while(Wire.available())
	{
		char readByte = Wire.read();
		Serial.print("0x");
		Serial.println(readByte, HEX);
	}
	Serial.println("");
}



