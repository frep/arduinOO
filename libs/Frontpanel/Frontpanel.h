/*
 * Frontpanel.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef FRONTPANEL_H_
#define FRONTPANEL_H_

#include <ArduinoSketch.h>
#include "NhdOledDisplay.h"
#include <VirtualButton.h>
#include <VirtualButtonEncoder.h>
#include "Adafruit_MCP23017.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// DISPLAY DEFINES
//////////////////////////////////////////////////////////////////////////////////////////////////

							// Display-Pin | Function | MCU-Pin
							// ================================
							//           1 | GND      | GND
							//           2 | VDD 3.3V | 3.3V
							//           3 | NC       | NC
#define    RS_PIN    14     //           4 | D/C      | D6 (variable)
							//        5-12 | GND      | GND
#define   SDI_PIN    16     //          13 | SDI      | D7
#define   SCL_PIN     2     //          14 | SCL      | D5
							//          15 | GND      | GND
#define   RES_PIN    12     //          16 | /RES     | D0 (variable)
#define    CS_PIN    13     //          17 | /CS      | D4
							//          18 | GND      | GND
                            //          19 | PS       | GND
							//          20 | CPU      | NC (only needed for parallel interface)

//////////////////////////////////////////////////////////////////////////////////////////////////
// MCP DEFINES
//////////////////////////////////////////////////////////////////////////////////////////////////

//   readGPIOAB():

//                  L  B  B  B  B        S  C  C  S  C  C
//                  O  U  U  U  U        W  H  H  W  H  H
//                  A  T  T  T  T        I  A  B  I  A  B
//                  D  4  3  2  1        2  2  2  1  1  1
//
//        B7 B6 B5 B4 B3 B2 B1 B0 A7 A6 A5 A4 A3 A2 A1 A0
// INPUT: 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

#define InputButNW 10
#define ButNWMask  0x0400
#define InputButNE  9
#define ButNEMask  0x0200
#define InputButSW 11
#define ButSWMask  0x0800
#define InputButSE  8
#define ButSEMask  0x0100

#define LoadOnMask 0x1000

#define EncA1	0
#define EncA1Mask  0x0001
#define EncB1	1
#define EncB1Mask  0x0002
#define But1	2
#define But1Mask   0x0004

#define EncA2	3
#define EncA2Mask  0x0008
#define EncB2	4
#define EncB2Mask  0x0010
#define But2	5
#define But2Mask   0x0020

//////////////////////////////////////////////////////////////////////////////////////////////////
// FRONTPANEL CLASS
//////////////////////////////////////////////////////////////////////////////////////////////////

class Frontpanel: public ArduinoSketch {
public:
	Frontpanel();
	virtual ~Frontpanel();
	void setup();
	void loop();

private:
	NhdOledDisplay*    					display;
	Adafruit_MCP23017* 					mcp;
	VirtualButton<Frontpanel>*			butNW;
	VirtualButton<Frontpanel>*  		butNE;
	VirtualButton<Frontpanel>*  		butSW;
	VirtualButton<Frontpanel>*  		butSE;
	VirtualButtonEncoder<Frontpanel>*	encV;
	VirtualButtonEncoder<Frontpanel>* 	encA;

	// setup functions
	void setupGpioExpander();
	void setupDisplay();
	void setupButtons();
	void setupEncoders();

	// loop functions
	void checkExpanderPins();
	void checkButtons();
	void checkEncoders();

	// helper functions
	bool bitIsSet(uint16_t registers, uint16_t bitmask);
	void printSetVoltage();
	void printSetCurrent();

	void incVoltage();
	void decVoltage();
	void incCurrent();
	void decCurrent();

	void butNWpressed();
	void butNEpressed();
	void butSWpressed();
	void butSEpressed();
	void encVpressed();
	void encApressed();

	// attributes
	uint16_t	lastReg;
	float 		startVoltage;
	float		maxVoltage;
	int			startCurrent;
	int			maxCurrent;

};

#endif /* FRONTPANEL_H_ */
