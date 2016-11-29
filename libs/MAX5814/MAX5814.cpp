/*
 * MAX5814.cpp
 *
 *  Created on: 29.11.2016
 *      Author: FREP
 */

#include "MAX5814.h"

	// DAC SELECTION:
	uint8_t MAX5814::dacA   = 0x00;
	uint8_t MAX5814::dacB   = 0x01;
	uint8_t MAX5814::dacC   = 0x02;
	uint8_t MAX5814::dacD   = 0x03;
	uint8_t MAX5814::dacAll = 0x04;

	// POWER MODES:
	uint8_t MAX5814::powerMode_Normal = 0x00;
	uint8_t MAX5814::powerMode_1kR    = 0x01;
	uint8_t MAX5814::powerMode_100KR  = 0x02;
	uint8_t MAX5814::powerMode_hiZ    = 0x03;

	// REF MODES:
	uint8_t MAX5814::refMode_ext = 0x00;
	uint8_t MAX5814::refMode_2V5 = 0x01;
	uint8_t MAX5814::refMode_2V0 = 0x02;
	uint8_t MAX5814::refMode_4V1 = 0x03;

	// CONFIG MODES:
	uint8_t MAX5814::latchOperational = 0x00;
	uint8_t MAX5814::latchTransparent = 0x01;

	// Commands:
	uint8_t MAX5814::cmd_codeN           = 0x00;
	uint8_t MAX5814::cmd_loadN           = 0x10;
	uint8_t MAX5814::cmd_codeN_loadAll   = 0x20;
	uint8_t MAX5814::cmd_codeN_loadN     = 0x30;
	uint8_t MAX5814::cmd_power           = 0x40;
	uint8_t MAX5814::cmd_swClear         = 0x50;
	uint8_t MAX5814::cmd_swReset         = 0x51;
	uint8_t MAX5814::cmd_config          = 0x60;
	uint8_t MAX5814::cmd_ref             = 0x70;
	uint8_t MAX5814::cmd_codeAll         = 0x80;
	uint8_t MAX5814::cmd_loadAll         = 0x81;
	uint8_t MAX5814::cmd_codeAll_loadAll = 0x82;


MAX5814::MAX5814(uint8_t address)
: address(address)
{}

MAX5814::~MAX5814(){}

void MAX5814::codeN(uint8_t dac, uint16_t value)
{
	uint8_t byte_cmd      = cmd_codeN | dac;
	uint8_t byte_dataHigh = (uint8_t)(value >> 2);
	uint8_t byte_dataLow  = (uint8_t)(value << 6);
	sendCmd(byte_cmd, byte_dataHigh, byte_dataLow);
}

void MAX5814::loadN(uint8_t dac)
{
	uint8_t byte_cmd = cmd_loadN | dac;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::power(uint8_t dac, uint8_t powerMode)
{
	uint8_t byte_cmd = cmd_power | powerMode;
	sendCmd(byte_cmd, dac2data(dac), 0x00);
}

void MAX5814::clear()
{
	sendCmd(cmd_swClear, 0x00, 0x00);
}

void MAX5814::reset()
{
	sendCmd(cmd_swReset, 0x00, 0x00);
}

void MAX5814::config(uint8_t dac, uint8_t configMode)
{
	uint8_t byte_cmd = cmd_config | configMode;
	sendCmd(byte_cmd, dac2data(dac), 0x00);
}

void MAX5814::setRef_Ext()
{
	uint8_t byte_cmd = cmd_ref | refMode_ext;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::setRef_2V5()
{
	uint8_t byte_cmd = cmd_ref | refMode_2V5;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::setRef_2V0()
{
	uint8_t byte_cmd = cmd_ref | refMode_2V0;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::setRef_4V1()
{
	uint8_t byte_cmd = cmd_ref | refMode_4V1;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::codeAll(uint16_t value)
{
	uint8_t byte_cmd      = cmd_codeAll;
	uint8_t byte_dataHigh = (uint8_t)(value >> 2);
	uint8_t byte_dataLow  = (uint8_t)(value << 6);
	sendCmd(byte_cmd, byte_dataHigh, byte_dataLow);
}

void MAX5814::loadAll()
{
	uint8_t byte_cmd = cmd_loadAll;
	sendCmd(byte_cmd, 0x00, 0x00);
}

void MAX5814::codeAll_loadAll(uint16_t value)
{
	uint8_t byte_cmd      = cmd_codeAll_loadAll;
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
}

uint8_t MAX5814::dac2data(uint8_t dac)
{
	switch(dac)
	{
	case dacA:
		return 0x01;
	case dacB:
		return 0x02;
	case dacC:
		return 0x04;
	case dacD:
		return 0x08;
	default:
	}
	return 0x00;
}

