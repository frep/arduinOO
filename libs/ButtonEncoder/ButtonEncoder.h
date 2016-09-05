#ifndef BUTTON_ENCODER_H
#define BUTTON_ENCODER_H

#include "Arduino.h"
#include "DigitalPin.h"
#include "Button.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// BUTTON_ENCODER DEFINES
//////////////////////////////////////////////////////////////////////////////////////////////////

// Values returned by 'check'
#define DIR_NONE 0x00
#define DIR_CW   0x10	// Clockwise step.
#define DIR_CCW  0x20	// Anti-clockwise step.

//////////////////////////////////////////////////////////////////////////////////////////////////
// BUTTON_ENCODER CLASS
//////////////////////////////////////////////////////////////////////////////////////////////////

class ButtonEncoder
{
public:
	ButtonEncoder(int CHA, int CHB, int BUT);
	virtual ~ButtonEncoder();
    void init();
    void check();
    boolean getValue();

    virtual void buttonPressed();
    virtual void buttonReleased();
    virtual void clockwiseTurn();
    virtual void counterClockwiseTurn();

protected:

    DigitalPin* chaPin;
    DigitalPin* chbPin;
    Button*     butPin;

    unsigned char state;
    unsigned char lastA;
    unsigned char lastB;
};

#endif /* BUTTON_ENCODER_H */
 
