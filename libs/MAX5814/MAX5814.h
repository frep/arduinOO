/*
 * MAX5814.h
 *
 *  Created on: 29.11.2016
 *      Author: FREP
 */

#ifndef MAX5814_H_
#define MAX5814_H_

#include <stdint.h>

class MAX5814 {
public:
	MAX5814(uint8_t address);
	virtual ~MAX5814();

	////////////////////////////////////////////////////////////////////////////
	// "HIGH" LEVEL FUNCTIONS
	////////////////////////////////////////////////////////////////////////////
	void codeA(uint16_t value){codeN(dacA, value);};
	void codeB(uint16_t value){codeN(dacB, value);};
	void codeC(uint16_t value){codeN(dacC, value);};
	void codeD(uint16_t value){codeN(dacD, value);};

	void loadA(){loadN(dacA);};
	void loadB(){loadN(dacB);};
	void loadC(){loadN(dacC);};
	void loadD(){loadN(dacD);};

	void powerA(uint8_t powerMode){power(dacA, powerMode);};
	void powerB(uint8_t powerMode){power(dacB, powerMode);};
	void powerC(uint8_t powerMode){power(dacC, powerMode);};
	void powerD(uint8_t powerMode){power(dacD, powerMode);};

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

	void configA(uint8_t configMode){config(dacA, configMode);};
	void configB(uint8_t configMode){config(dacB, configMode);};
	void configC(uint8_t configMode){config(dacC, configMode);};
	void configD(uint8_t configMode){config(dacD, configMode);};

	void setRef_Ext();
	void setRef_2V5();
	void setRef_2V0();
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

private:

	uint8_t address;

	// DAC SELECTION:
	static uint8_t dacA;
	static uint8_t dacB;
	static uint8_t dacC;
	static uint8_t dacD;
	static uint8_t dacAll;

	// POWER MODES:
	static uint8_t powerMode_Normal;
	static uint8_t powerMode_1kR;
	static uint8_t powerMode_100KR;
	static uint8_t powerMode_hiZ;

	// REF MODES:
	static uint8_t refMode_ext;
	static uint8_t refMode_2V5;
	static uint8_t refMode_2V0;
	static uint8_t refMode_4V1;

	// CONFIG MODES:
	static uint8_t latchOperational;
	static uint8_t latchTransparent;

	// Commands:
	static uint8_t cmd_codeN;
	static uint8_t cmd_loadN;
	static uint8_t cmd_codeN_loadAll;
	static uint8_t cmd_codeN_loadN;
	static uint8_t cmd_power;
	static uint8_t cmd_swClear;
	static uint8_t cmd_swReset;
	static uint8_t cmd_config;
	static uint8_t cmd_ref;
	static uint8_t cmd_codeAll;
	static uint8_t cmd_loadAll;
	static uint8_t cmd_codeAll_loadAll;

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


	void sendCmd(uint8_t byte_cmd, uint8_t byte_dataHigh, uint8_t byte_dataLow);
	uint8_t dac2data(uint8_t dac);

};

#endif /* MAX5814_H_ */
