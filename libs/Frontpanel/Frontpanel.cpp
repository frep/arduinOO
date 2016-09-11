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

	// Statemachine
	currentState = NULL;
	stateDefault = new StateDefault(this);
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
	delete stateDefault;
}

void Frontpanel::setup()
{
	EEPROM.begin(512);
	Serial.begin(115200);
	while(!Serial){}
	readConfig();
	setupButtons();
	setupGpioExpander();
	setupEncoders();
	setupDisplay();
	setCurrentState(stateDefault);
	Serial.println("init done!");
	printMemoryInfo();
	printSketchInfos();
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

void Frontpanel::writeConfig()
{
	Serial.println("Writing Config");
	EEPROM_write(0,'C');
	EEPROM_write(1,'F');
	EEPROM_write(2,'G');

	EEPROM_write(16,startVoltage);	// Voltage [V]  (4 Bytes)
	EEPROM_write(20,startCurrent);	// Current [mA] (4 Bytes)

	EEPROM.commit();
}

boolean Frontpanel::readConfig()
{
	Serial.println("Reading Configuration");
	if( EEPROM_check(0,'C') && EEPROM_check(1,'F') && EEPROM_check(2,'G') )
	{
		Serial.println("Configurarion Found!");
		EEPROM_read(16,startVoltage);
		EEPROM_read(20,startCurrent);
		return true;
	}
	else
	{
		Serial.println("Configurarion NOT FOUND!!!!");
		return false;
	}
}

void Frontpanel::butNWpressed()
{
	currentState->butNWpressed();
}

void Frontpanel::butNEpressed()
{
	currentState->butNEpressed();
}

void Frontpanel::butSWpressed()
{
	currentState->butSWpressed();
}

void Frontpanel::butSEpressed()
{
	currentState->butSEpressed();
}

void Frontpanel::encVpressed()
{
	currentState->encVpressed();
}

void Frontpanel::encApressed()
{
	currentState->encApressed();
}

void Frontpanel::encVcwTurn()
{
	currentState->encVcwTurn();
}

void Frontpanel::encVccwTurn()
{
	currentState->encVccwTurn();
}

void Frontpanel::encAcwTurn()
{
	currentState->encAcwTurn();
}

void Frontpanel::encAccwTurn()
{
	currentState->encAccwTurn();
}

void Frontpanel::setCurrentState(FrontpanelState* newState)
{
	currentState = newState;
	// update display
	currentState->showDisplay();
}

FrontpanelState* Frontpanel::getStateDefault()
{
	return stateDefault;
}

void Frontpanel::setupEncoders()
{
	// "Voltage"-Encoder
	encV->init();
	encV->attachFunctionOnCWTurn(this,                &Frontpanel::encVcwTurn);
	encV->attachFunctionOnCCWTurn(this,               &Frontpanel::encVccwTurn);
	encV->butPin->attachFunctionOnButtonPressed(this, &Frontpanel::encVpressed);

	// "Current"-Encoder
	encA->init();
	encA->attachFunctionOnCWTurn(this,                &Frontpanel::encAcwTurn);
	encA->attachFunctionOnCCWTurn(this,               &Frontpanel::encAccwTurn);
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
}
