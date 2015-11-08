#include "arduinOO.h"
#include "ButtonIndicator.h"

#define activeLow true
#define activeHigh false

ButtonIndicator sketch;

//The setup function is called once at startup of the sketch
void setup()
{
	sketch.setup();
}

// The loop function is called in an endless loop
void loop()
{
	sketch.loop();
}
