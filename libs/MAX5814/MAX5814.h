/*
 * MAX5814.h
 *
 *  Created on: 29.11.2016
 *      Author: FREP
 */

#ifndef MAX5814_H_
#define MAX5814_H_

#include <stdint.h>

	////////////////////////////////////////////////////////////////////////////
	// FOOTPRINT (TSSOP)
	////////////////////////////////////////////////////////////////////////////
	//          _____________
	//         |             |
	//   REF --| 01   M   14 |-- /LDAC
	//  OUTA --| 02   A   13 |-- V_DDIO
	//  OUTB --| 03   X   12 |-- /CLR
	//   GND --| 04   5   11 |-- SDA
	//  OUTC --| 05   8   10 |-- SCL
	//  OUTD --| 06   1   09 |-- ADDR0
	//   VDD --| 07   4   08 |-- ADDR1
	//         |_____________|

class MAX5814 {
public:
	MAX5814(uint8_t address);
	virtual ~MAX5814();

	////////////////////////////////////////////////////////////////////////////
	// "HIGH" LEVEL FUNCTIONS
	////////////////////////////////////////////////////////////////////////////

	/**
	 * Writes value to the CODE register of DAC A:
	 * MAX5814 has 10bit channels: value-range is from 0 to 1023
	 */
	void codeA(uint16_t value){codeN(0x00, value);};
	/**
	 * Writes value to the CODE register of DAC B:
	 * MAX5814 has 10bit channels: value-range is from 0 to 1023
	 */
	void codeB(uint16_t value){codeN(0x01, value);};
	/**
	 * Writes value to the CODE register of DAC C:
	 * MAX5814 has 10bit channels: value-range is from 0 to 1023
	 */
	void codeC(uint16_t value){codeN(0x02, value);};
	/**
	 * Writes value to the CODE register of DAC D:
	 * MAX5814 has 10bit channels: value-range is from 0 to 1023
	 */
	void codeD(uint16_t value){codeN(0x03, value);};

	/**
	 * Loads the data of the CODE register A into the DAC register A
	 */
	void loadA(){loadN(0x00);};
	/**
	 * Loads the data of the CODE register B into the DAC register B
	 */
	void loadB(){loadN(0x01);};
	/**
	 * Loads the data of the CODE register C into the DAC register C
	 */
	void loadC(){loadN(0x02);};
	/**
	 * Loads the data of the CODE register D into the DAC register D
	 */
	void loadD(){loadN(0x03);};

	/**
	 * Sets the powermode of DAC A. The different modes are:
	 * 	powerMode_Normal: normal operation
	 *  powerMode_1kR:    Power-down with internal 1kR pulldown to GND
	 *  powerMode_100KR:  Power-down with internal 100kR pulldown to GND
	 *  powerMode_hiZ:    Power-down with high-impedance output
	 */
	void powerA(uint8_t powerMode){power(0x00, powerMode);};
	/**
	 * Sets the powermode of DAC B. The different modes are:
	 * 	powerMode_Normal: normal operation
	 *  powerMode_1kR:    Power-down with internal 1kR pulldown to GND
	 *  powerMode_100KR:  Power-down with internal 100kR pulldown to GND
	 *  powerMode_hiZ:    Power-down with high-impedance output
	 */
	void powerB(uint8_t powerMode){power(0x01, powerMode);};
	/**
	 * Sets the powermode of DAC C. The different modes are:
	 * 	powerMode_Normal: normal operation
	 *  powerMode_1kR:    Power-down with internal 1kR pulldown to GND
	 *  powerMode_100KR:  Power-down with internal 100kR pulldown to GND
	 *  powerMode_hiZ:    Power-down with high-impedance output
	 */
	void powerC(uint8_t powerMode){power(0x02, powerMode);};
	/**
	 * Sets the powermode of DAC D. The different modes are:
	 * 	powerMode_Normal: normal operation
	 *  powerMode_1kR:    Power-down with internal 1kR pulldown to GND
	 *  powerMode_100KR:  Power-down with internal 100kR pulldown to GND
	 *  powerMode_hiZ:    Power-down with high-impedance output
	 */
	void powerD(uint8_t powerMode){power(0x03, powerMode);};

	/**
	 * Executes a software clear (all CODE and DAC registers cleared
	 * to their default values)
	 */
	void clear();

	/**
	 * Executes a software reset (all CODE, DAC, and control registers
	 * returned to their default values)
	 */
	void reset();

	/**
	 * Configures latch behaviour of DAC A. the different modes are:
	 *  latchOperational: DAC reg is updated by LOAD cmd or /LDAC
	 *  latchTransparent: DAC reg is updated with new CODE reg value
	 */
	void configA(uint8_t configMode){config(0x00, configMode);};
	/**
	 * Configures latch behaviour of DAC B. the different modes are:
	 *  latchOperational: DAC reg is updated by LOAD cmd or /LDAC
	 *  latchTransparent: DAC reg is updated with new CODE reg value
	 */
	void configB(uint8_t configMode){config(0x01, configMode);};
	/**
	 * Configures latch behaviour of DAC C. the different modes are:
	 *  latchOperational: DAC reg is updated by LOAD cmd or /LDAC
	 *  latchTransparent: DAC reg is updated with new CODE reg value
	 */
	void configC(uint8_t configMode){config(0x02, configMode);};
	/**
	 * Configures latch behaviour of DAC D. the different modes are:
	 *  latchOperational: DAC reg is updated by LOAD cmd or /LDAC
	 *  latchTransparent: DAC reg is updated with new CODE reg value
	 */
	void configD(uint8_t configMode){config(0x03, configMode);};

	/**
	 * Set REF-pin to read an external reference voltage.
	 */
	void setRef_Ext();
	/**
	 * Set an internal voltage reference of 2.500V. This voltage is
	 * available on the REF-pin for other external circuitry and
	 * can drive a 25kR load.
	 */
	void setRef_2V5();
	/**
	 * Set an internal voltage reference of 2.048V. This voltage is
	 * available on the REF-pin for other external circuitry and
	 * can drive a 25kR load.
	 */
	void setRef_2V0();
	/**
	 * Set an internal voltage reference of 4.096V. This voltage is
	 * available on the REF-pin for other external circuitry and
	 * can drive a 25kR load.
	 */
	void setRef_4V1();

	/**
	 * Writes data to all CODE registers
	 */
	void codeAll(uint16_t value);

	/**
	 * Updates all DAC latches with current CODE register data
	 */
	void loadAll();

	/**
	 * Simulaneously writes data to all CODE registers while
	 * updating all DAC registers.
	 */
	void codeAll_loadAll(uint16_t value);

	void readbackCmd();

private:

	uint8_t address;

	////////////////////////////////////////////////////////////////////////////
	// CONSTANTS
	////////////////////////////////////////////////////////////////////////////

	// POWER MODES:
	static const uint8_t powerMode_Normal;
	static const uint8_t powerMode_1kR;
	static const uint8_t powerMode_100KR;
	static const uint8_t powerMode_hiZ;

	// CONFIG MODES:
	static const uint8_t latchOperational;
	static const uint8_t latchTransparent;

	////////////////////////////////////////////////////////////////////////////
	// LOW LEVEL FUNCTIONS
	////////////////////////////////////////////////////////////////////////////

	/**
	 * Writes value to the selected CODE register(s)
	 */
	void codeN(uint8_t dac, uint16_t value);

	/**
	 * Transfers data from the selected CODE register(s) to the selected DAC
	 * register(s)
	 */
	void loadN(uint8_t dac);

	/**
	 * Sets the power mode of the selected DACs (DACs selected with a 1 in
	 * the corresponding DACn bit are updated, DACs with a 0 in the
	 * correspondign DACn bit are not impacted)
	 */
	void power(uint8_t dac, uint8_t powerMode);

	/**
	 * Sets the DAC Latch Mode of the selected DACs. Only DACs with a 1 in the
	 * selection bit are updated y the command.
	 * Mode: latchOperational (LOAD and LDAC-Pin controlled)
	 *       latchTransparent latch is transparent
	 */
	void config(uint8_t dac, uint8_t configMode);

	/**
	 * Implementation of a single register write sequence:
	 * Slaveaddress, command, data high byte, data low byte.
	 * (Slave address is transmitted by instruction "beginTransmission")
	 */
	void sendCmd(uint8_t byte_cmd, uint8_t byte_dataHigh, uint8_t byte_dataLow);

	/**
	 * Sets command-bits according to the corresponding DAC.
	 */
	uint8_t dac2data(uint8_t dac);

};

#endif /* MAX5814_H_ */
