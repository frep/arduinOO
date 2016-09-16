/*
 * Frontpanel.cpp
 *
 *  Created on: 03.09.2016
 *      Author: frehnerp
 */

#include "Frontpanel.h"
#include "frep.h"

Frontpanel::Frontpanel()
: lastReg(0), startVoltage(5.1), maxVoltage(30.0), startCurrent(500), maxCurrent(2000), loadCurrentIndex(numberLoadCurValues-1),
  loadCurrents{ 50,  75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500, 525, 550,
	           575, 600, 625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000}
{
	display = new NhdOledDisplay(160, 128, SDI_PIN, SCL_PIN, RS_PIN, RES_PIN, CS_PIN);
	mcp     = new Adafruit_MCP23017();
	butNW   = new VirtualButton<Frontpanel>(activeLow);
	butNE   = new VirtualButton<Frontpanel>(activeLow);
	butSW   = new VirtualButton<Frontpanel>(activeLow);
	butSE   = new VirtualButton<Frontpanel>(activeLow);
	encV    = new VirtualButtonEncoder<Frontpanel>();
	encA    = new VirtualButtonEncoder<Frontpanel>();
	digPot  = new AD5274(AD5274_address, MAX_RES);

	// Statemachine
	currentState     = NULL;
	stateDefault     = new StateDefault(this);
	stateLoadCurrent = new StateLoadCurrent(this);
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
	delete digPot;
}

void Frontpanel::setup()
{
	EEPROM.begin(512);
	Serial.begin(115200);
	Wire.begin();
	while(!Serial){}
	readConfig();
	setupButtons();
	setupGpioExpander();
	setupEncoders();
	setupDigPot();
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

uint16_t Frontpanel::digPotValue4loadCurrent(uint16_t milliamp)
{
	if(milliamp >1000)
	{
		milliamp = 1000;
	}
	uint16_t returnValue = ((1000000 / milliamp) - 1000);
	Serial.print("load current: ");
	Serial.print(milliamp);
	Serial.print("mA corresponds to R = ");
	Serial.println(returnValue);
	return returnValue;
}

void Frontpanel::writeConfig()
{
	Serial.println("Writing Config");
	EEPROM_write(0,'C');
	EEPROM_write(1,'F');
	EEPROM_write(2,'G');

	EEPROM_write(16,startVoltage);	    // Voltage [V]
	EEPROM_write(20,startCurrent);	    // Current [mA]
	EEPROM_write(24,loadCurrentIndex);	// [uint8_t]

	EEPROM.commit();
}

boolean Frontpanel::readConfig()
{
	Serial.println("Reading Configuration");
	if( EEPROM_check(0,'C') && EEPROM_check(1,'F') && EEPROM_check(2,'G') )
	{
		Serial.println("Configuration Found!");
		EEPROM_read(16,startVoltage);
		EEPROM_read(20,startCurrent);
		EEPROM_read(24, loadCurrentIndex);
		return true;
	}
	else
	{
		Serial.println("Configuration NOT FOUND!!!!");
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

FrontpanelState* Frontpanel::getStateLoadCurrent()
{
	return stateLoadCurrent;
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

void Frontpanel::setupDigPot()
{
	digPot->init();
	digPot->setResistor(digPotValue4loadCurrent(loadCurrents[loadCurrentIndex]));
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

uint8_t Frontpanel::getPrevLoadCurrentIndex()
{
	if((loadCurrentIndex-1) < 0)
	{
		return numberLoadCurValues-1;
	}
	return (loadCurrentIndex-1);
}

uint8_t Frontpanel::getNextLoadCurrentIndex()
{
	return ((loadCurrentIndex+1)%numberLoadCurValues);
}

void Frontpanel::printLoadCurrents()
{
	display->printInt2xCentered(59,loadCurrents[loadCurrentIndex],4,display->GREEN, display->BLACK);
	display->printIntCentered(64,28,loadCurrents[getPrevLoadCurrentIndex()],4,display->GREEN, display->BLACK);
	display->printIntCentered(64,132,loadCurrents[getNextLoadCurrentIndex()],4,display->GREEN, display->BLACK);
}




