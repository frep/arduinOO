/*
 * EspChip.h
 *
 *  Created on: 11.09.2016
 *      Author: frehnerp
 */

#ifndef ESP_H_
#define ESP_H_

#include "Arduino.h"
#include <EEPROM.h>

class EspChip {
public:
	virtual ~EspChip(){}
protected:

	// EEPROM - methods
	void EEPROM_erase(int eepromSize)
	{
		Serial.println("erase EEPROM");
		for (int i = 0; i < eepromSize; i++)
		{
		    EEPROM.write(i, 0);
		}
		EEPROM.end();
	}

	// Arguments: "ee"    specifies the EEPROM startaddres
	//            "value" to be written into EEPROM
	// return:    Number of bytes needed to write value
	template <class T>
	int EEPROM_write(int ee, const T& value)
	{
		const byte* p = (const byte*)(const void*)&value;
		int i;
		for (i = 0; i < sizeof(value); i++)
			EEPROM.write(ee++, *p++);
		return i;
	}

	template <class T>
	int EEPROM_read(int ee, T& value)
	{
		byte* p = (byte*)(void*)&value;
		int i;
		for (i = 0; i < sizeof(value); i++)
			*p++ = EEPROM.read(ee++);
		return i;
	}

	template <class T>
	bool EEPROM_check(int ee, T value)
	{
		T eepromValue;
		EEPROM_read(ee, eepromValue);
		if(eepromValue == value)
		{
			return true;
		}
		return false;
	}

	void printMemoryInfo()
	{
		Serial.print("free Memory [Bytes]: ");
		Serial.println(ESP.getFreeHeap());
	}

	void printSketchInfos()
	{
		Serial.print("used sketch size [Bytes]: ");
		Serial.println(ESP.getSketchSize());
		Serial.print("free sketch size [Bytes]: ");
		Serial.println(ESP.getFreeSketchSpace());
	}

};

#endif /* ESP_H_ */
