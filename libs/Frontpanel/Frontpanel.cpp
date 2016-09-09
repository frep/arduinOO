/*
 * Frontpanel.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "Frontpanel.h"
#include "frep.h"

Frontpanel::Frontpanel()
: lastReg(0), startVoltage(5.1), maxVoltage(30.0), startCurrent(500), maxCurrent(2000)
{
	display = new NhdOledDisplay(160, 128, SDI_PIN, SCL_PIN, RS_PIN, RES_PIN, CS_PIN);
	mcp     = new Adafruit_MCP23017();
	butNW   = new VirtualButton<Frontpanel>(activeLow);
	butNE   = new VirtualButton<Frontpanel>(activeLow);
	butSW   = new VirtualButton<Frontpanel>(activeLow);
	butSE   = new VirtualButton<Frontpanel>(activeLow);
	encV    = new VirtualButtonEncoder<Frontpanel>();
	encA    = new VirtualButtonEncoder<Frontpanel>();
}

Frontpanel::~Frontpanel()
{
	delete display;
	delete mcp;
	delete butNW;
	delete butNE;
	delete butSW;
	delete butSE;
	delete encV;
	delete encA;
}

void Frontpanel::setup()
{
	setupButtons();
	setupGpioExpander();
	setupEncoders();
	setupDisplay();
	Serial.begin(115200);
	while(!Serial){}
	Serial.println("init done!");
}

void Frontpanel::loop()
{
	checkExpanderPins();
	checkButtons();
	checkEncoders();
}

void Frontpanel::checkExpanderPins()
{
	// read registers
	uint16_t regBA = mcp->readGPIOAB();

	butNW->write(bitIsSet(regBA, ButNWMask));
	butSW->write(bitIsSet(regBA, ButSWMask));
	butNE->write(bitIsSet(regBA, ButNEMask));
	butSE->write(bitIsSet(regBA, ButSEMask));

	encV->setChA(bitIsSet(regBA, EncA1Mask));
	encV->setChB(bitIsSet(regBA, EncB1Mask));
	encV->setBut(bitIsSet(regBA, But1Mask));

	encA->setChA(bitIsSet(regBA, EncA2Mask));
	encA->setChB(bitIsSet(regBA, EncB2Mask));
	encA->setBut(bitIsSet(regBA, But2Mask));

/*
	if(regBA != lastReg)
	{
		lastReg = regBA;
		Serial.print("Register BA: ");
		Serial.println(regBA, BIN);
	}
*/
}

bool Frontpanel::bitIsSet(uint16_t registers, uint16_t bitmask)
{
	if((registers & bitmask) > 0)
	{
		return true;
	}

	return false;
}

void Frontpanel::printSetVoltage()
{
	String setString;
	if(startVoltage >= 10.0)
	{
		setString = "Set: ";
	}
	else
	{
		setString = "Set:  ";
	}
	String setVoltage = setString + startVoltage;
	display->printTextCentered(85, 40, setVoltage, display->RED, display->BLACK);
}

void Frontpanel::printSetCurrent()
{
	String setString;
	if(startCurrent >= 1000)
	{
		setString = "Set: ";
	}
	else if(startCurrent >= 100 && startCurrent < 1000)
	{
		setString = "Set:  ";
	}
	else if(startCurrent >= 10 && startCurrent < 100)
	{
		setString = "Set:   ";
	}
	else
	{
		setString = "Set:    ";
	}
	String setCurrent = setString + startCurrent;
	display->printTextCentered(85, 120, setCurrent, display->RED, display->BLACK);
}

void Frontpanel::incVoltage()
{
	Serial.println("increase Voltage");
	if(startVoltage < maxVoltage)
	{
		startVoltage += 0.1;
		printSetVoltage();
	}
}

void Frontpanel::decVoltage()
{
	Serial.println("decrease Voltage");
	if(startVoltage > 0)
	{
		startVoltage -= 0.1;
		printSetVoltage();
	}
}

void Frontpanel::incCurrent()
{
	Serial.println("increase Current");
	if(startCurrent < maxCurrent)
	{
		startCurrent += 10;
		printSetCurrent();
	}
}

void Frontpanel::decCurrent()
{
	Serial.println("decrease Current");
	if(startCurrent > 0)
	{
		startCurrent -= 10;
		printSetCurrent();
	}
}

void Frontpanel::butNWpressed()
{
	Serial.println("button NW pressed");
}

void Frontpanel::butNEpressed()
{
	Serial.println("button NE pressed");
}

void Frontpanel::butSWpressed()
{
	Serial.println("button SW pressed");
}

void Frontpanel::butSEpressed()
{
	Serial.println("button SE pressed");
}

void Frontpanel::encVpressed()
{
	Serial.println("button encV pressed");
}

void Frontpanel::encApressed()
{
	Serial.println("button encA pressed");
}

void Frontpanel::setupEncoders()
{
	// "Voltage"-Encoder
	encV->init();
	encV->attachFunctionOnCWTurn(this,  &Frontpanel::incVoltage);
	encV->attachFunctionOnCCWTurn(this, &Frontpanel::decVoltage);
	encV->butPin->attachFunctionOnButtonPressed(this, &Frontpanel::encVpressed);

	// "Current"-Encoder
	encA->init();
	encA->attachFunctionOnCWTurn(this,  &Frontpanel::incCurrent);
	encA->attachFunctionOnCCWTurn(this, &Frontpanel::decCurrent);
	encA->butPin->attachFunctionOnButtonPressed(this, &Frontpanel::encApressed);
}

void Frontpanel::setupButtons()
{
	butNW->init();
	butNW->attachFunctionOnButtonPressed(this, &Frontpanel::butNWpressed);
	butSW->init();
	butSW->attachFunctionOnButtonPressed(this, &Frontpanel::butSWpressed);
	butNE->init();
	butNE->attachFunctionOnButtonPressed(this, &Frontpanel::butNEpressed);
	butSE->init();
	butSE->attachFunctionOnButtonPressed(this, &Frontpanel::butSEpressed);
}

void Frontpanel::checkEncoders()
{
	encV->check();
	encA->check();
}

void Frontpanel::checkButtons()
{
	butNW->checkButton();
	butSW->checkButton();
	butNE->checkButton();
	butSE->checkButton();
}

void Frontpanel::setupGpioExpander()
{
	mcp->begin();      					// use default address 0
	mcp->pinMode(InputButNW, INPUT);
	mcp->pinMode(InputButSW, INPUT);
	mcp->pinMode(InputButNE, INPUT);
	mcp->pinMode(InputButSE, INPUT);

	mcp->pinMode(EncA1, INPUT);
	mcp->pinMode(EncB1, INPUT);
	mcp->pinMode(But1,  INPUT);
	mcp->pinMode(EncA2, INPUT);
	mcp->pinMode(EncB2, INPUT);
	mcp->pinMode(But2,  INPUT);
}

void Frontpanel::setupDisplay()
{
	display->init();
	// fill screen with black
	display->fillScreen(display->YELLOW);
	// show frep image
	display->printImage(50, 0, frep60x80, 60, 80);
	// show title
	display->printText2xCentered(103, "frep's",    display->BLACK, display->YELLOW);
	display->printText2xCentered( 83, "bench PSU", display->BLACK, display->YELLOW);

	delay(2000);

	display->fillScreen(display->BLACK);

	display->drawButton(10,   0, 60, 20, "Lipo 1s",  display->BLACK, display->YELLOW);
	display->drawButton(90,   0, 60, 20, "Load",     display->BLACK, display->YELLOW);
	display->drawButton(10, 108, 60, 20, "Settings", display->BLACK, display->YELLOW);
	display->drawButton(90, 108, 60, 20, "Save",     display->BLACK, display->YELLOW);

	float fakeVoltage = 5.16;	// Voltage
	int fakeCurrent = 5;		// Milliamps
	display->printFloat2xCentered(56,  40, fakeVoltage, 1, display->GREEN, display->BLACK);
	display->printInt2xCentered(  56, 120, fakeCurrent, 4, display->GREEN, display->BLACK);

	printSetVoltage();
	printSetCurrent();

	display->printTextCentered(35,  40, "Volts",     display->GREEN, display->BLACK);
	display->printTextCentered(35, 120, "Milliamps", display->GREEN, display->BLACK);
}
