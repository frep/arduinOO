/*
 * Frontpanel.h
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#ifndef FRONTPANEL_H_
#define FRONTPANEL_H_

#include <ArduinoSketch.h>
#include <EspChip.h>
#include "NhdOledDisplay.h"
#include <VirtualButton.h>
#include <VirtualButtonEncoder.h>
#include "Adafruit_MCP23017.h"
#include <EEPROM.h>

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
// AD5274  DEFINES
//////////////////////////////////////////////////////////////////////////////////////////////////
#define AD5274_address 0x2C

//////////////////////////////////////////////////////////////////////////////////////////////////
// FRONTPANEL CLASS
//////////////////////////////////////////////////////////////////////////////////////////////////

// forward declarations
class FrontpanelState;
class StateDefault;

class Frontpanel: public ArduinoSketch, public EspChip
{
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

	// EEPROM-based configurations
	void writeConfig();
	boolean readConfig();

	// ---------------------------------------------------------------
	// Context (State pattern)
	// Operations: these actions can differ based on the current state
	// So, each state has to implement these.
	void butNWpressed();
	void butNEpressed();
	void butSWpressed();
	void butSEpressed();
	void encVpressed();
	void encApressed();
	void encVccwTurn();
	void encVcwTurn();
	void encAccwTurn();
	void encAcwTurn();

	void showDisplay();

	FrontpanelState* currentState;
	friend           StateDefault;
	StateDefault*    stateDefault;
	void             setCurrentState(FrontpanelState* newState);
	FrontpanelState* getStateDefault();


	// ---------------------------------------------------------------

	// attributes
	uint16_t	lastReg;
	float 		startVoltage;
	float		maxVoltage;
	uint16_t	startCurrent;
	uint16_t	maxCurrent;

};

//////////////////////////////////////////////////////////////////////////////////////////////////
// FRONTPANEL STATES
//////////////////////////////////////////////////////////////////////////////////////////////////

class FrontpanelState
{
 public:
	FrontpanelState(Frontpanel* context)
 	:context(context)
 	{
 	}
	virtual ~FrontpanelState(){}
	virtual void butNWpressed()
	{
		Serial.println("button NW pressed");
	}
	virtual void butNEpressed()
	{
		Serial.println("button NE pressed");
	}
	virtual void butSWpressed()
	{
		Serial.println("button SW pressed");
	}
	virtual void butSEpressed()
	{
		Serial.println("button SE pressed");
	}
	virtual void encVpressed()
	{
		Serial.println("button encV pressed");
	}
	virtual void encApressed()
	{
		Serial.println("button encA pressed");
	}
	virtual void encVccwTurn()
	{
		Serial.println("encV counterclockwise turn");
	}
	virtual void encVcwTurn()
	{
		Serial.println("encV clockwise turn");
	}
	virtual void encAccwTurn()
	{
		Serial.println("encA counterclockwise turn");
	}
	virtual void encAcwTurn()
	{
		Serial.println("encA clockwise turn");
	}
	virtual void showDisplay() = 0;
 protected:
	Frontpanel* context;
};

class StateDefault : public FrontpanelState
{
public:
	StateDefault(Frontpanel* context)
	: FrontpanelState(context)
	{}
	void encVpressed()
	{
		context->writeConfig();
	}
	void encApressed()
	{
		context->writeConfig();
	}
	void encVcwTurn()
	{
		context->incVoltage();
	}
	void encVccwTurn()
	{
		context->decVoltage();
	}
	void encAcwTurn()
	{
		context->incCurrent();
	}
	void encAccwTurn()
	{
		context->decCurrent();
	}
	void showDisplay()
	{
		context->display->fillScreen(context->display->BLACK);

		// Button SW
		context->display->drawButton(10,   0, 60, 20, "Lipo 1s",  context->display->BLACK, context->display->YELLOW);
		// Button SE
		context->display->drawButton(90,   0, 60, 20, "Load",     context->display->BLACK, context->display->YELLOW);
		// Button NW
		context->display->drawButton(10, 108, 60, 20, "Settings", context->display->BLACK, context->display->YELLOW);
		// Button NE
		context->display->drawButton(90, 108, 60, 20, "Save",     context->display->BLACK, context->display->YELLOW);

		float fakeVoltage = 5.16;	// Voltage
		int fakeCurrent = 5;		// Milliamps
		context->display->printFloat2xCentered(56,  40, fakeVoltage, 1, context->display->GREEN, context->display->BLACK);
		context->display->printInt2xCentered(  56, 120, fakeCurrent, 4, context->display->GREEN, context->display->BLACK);

		context->printSetVoltage();
		context->printSetCurrent();

		context->display->printTextCentered(35,  40, "Volts",     context->display->GREEN, context->display->BLACK);
		context->display->printTextCentered(35, 120, "Milliamps", context->display->GREEN, context->display->BLACK);
	}
};



#endif /* FRONTPANEL_H_ */
