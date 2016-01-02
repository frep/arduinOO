/*
 * NhdOledDisplay.cpp
 *
 *  Created on: 25.12.2015
 *      Author: frehnerp
 */

#include "NhdOledDisplay.h"
#include <Arduino.h>
#include <fonts.h>


NhdOledDisplay::NhdOledDisplay(unsigned int displayWidth,
	                           unsigned int displayHeight,
							   uint8_t SDI,
	       	   	   	   	   	   uint8_t SCL,
							   uint8_t RS,
							   uint8_t RES,
							   uint8_t CS,
							   uint8_t PS)
: width(displayWidth)
, height(displayHeight)
, SDI_PIN(SDI)
, SCL_PIN(SCL)
, RS_PIN(RS)
, RES_PIN(RES)
, CS_PIN(CS)
, PS_PIN(PS)
{
	RED    = 0x0000FF;
	GREEN  = 0x00FF00;
	BLUE   = 0xFF0000;
	WHITE  = 0xFFFFFF;
	BLACK  = 0x000000;
	YELLOW = 0x98f1fc;
}

NhdOledDisplay::~NhdOledDisplay()
{

}

void NhdOledDisplay::init()
{
	pinConfiguration();
	OLED_Init_160128RGB();
}

void NhdOledDisplay::pinConfiguration()
{
    pinMode(RS_PIN,  OUTPUT);		// configure RS_PIN as output
    pinMode(RES_PIN, OUTPUT);       // configure RES_PIN as output
    pinMode(CS_PIN,  OUTPUT);       // configure CS_PIN as output
    pinMode(PS_PIN,  OUTPUT);       // configure PS_PIN as output
    pinMode(SDI_PIN, OUTPUT);       // configure SDI_PIN as output
    pinMode(SCL_PIN, OUTPUT);       // configure SCL_PIN as output
    digitalWrite(CS_PIN, HIGH);     // set CS_PIN
    digitalWrite(PS_PIN, LOW);      // reset PS_PIN
}

//OLED initialization
void NhdOledDisplay::OLED_Init_160128RGB(void)
{
    digitalWrite(RES_PIN, LOW);
    delay(500);
    digitalWrite(RES_PIN, HIGH);
    delay(500);

    OLED_Command_160128RGB(0x04);// Set Normal Driving Current
    OLED_Data_160128RGB(0x03);// Disable Oscillator Power Down
    delay(2);
    OLED_Command_160128RGB(0x04); // Enable Power Save Mode
    OLED_Data_160128RGB(0x00); // Set Normal Driving Current
    delay(2); // Disable Oscillator Power Down
    OLED_Command_160128RGB(0x3B);
    OLED_Data_160128RGB(0x00);
    OLED_Command_160128RGB(0x02);
    OLED_Data_160128RGB(0x01); // Set EXPORT1 Pin at Internal Clock
    // Oscillator operates with external resister.
    // Internal Oscillator On
    OLED_Command_160128RGB(0x03);
    OLED_Data_160128RGB(0x90); // Set Clock as 90 Frames/Sec
    OLED_Command_160128RGB(0x80);
    OLED_Data_160128RGB(0x01); // Set Reference Voltage Controlled by External Resister
    OLED_Command_160128RGB(0x08);// Set Pre-Charge Time of Red
    OLED_Data_160128RGB(0x04);
    OLED_Command_160128RGB(0x09);// Set Pre-Charge Time of Green
    OLED_Data_160128RGB(0x05);
    OLED_Command_160128RGB(0x0A);// Set Pre-Charge Time of Blue
    OLED_Data_160128RGB(0x05);
    OLED_Command_160128RGB(0x0B);// Set Pre-Charge Current of Red
    OLED_Data_160128RGB(0x9D);
    OLED_Command_160128RGB(0x0C);// Set Pre-Charge Current of Green
    OLED_Data_160128RGB(0x8C);
    OLED_Command_160128RGB(0x0D);// Set Pre-Charge Current of Blue
    OLED_Data_160128RGB(0x57);
    OLED_Command_160128RGB(0x10);// Set Driving Current of Red
    OLED_Data_160128RGB(0x56);
    OLED_Command_160128RGB(0x11);// Set Driving Current of Green
    OLED_Data_160128RGB(0x4D);
    OLED_Command_160128RGB(0x12);// Set Driving Current of Blue
    OLED_Data_160128RGB(0x46);
    OLED_Command_160128RGB(0x13);
    OLED_Data_160128RGB(0xA0); // Set Color Sequence
    OLED_Command_160128RGB(0x14);
    OLED_Data_160128RGB(0x01); // Set MCU Interface Mode
    OLED_Command_160128RGB(0x16);
    OLED_Data_160128RGB(0x76); // Set Memory Write Mode
    OLED_Command_160128RGB(0x28);
    OLED_Data_160128RGB(0x7F); // 1/128 Duty (0x0F~0x7F)
    OLED_Command_160128RGB(0x29);
    OLED_Data_160128RGB(0x00); // Set Mapping RAM Display Start Line (0x00~0x7F)
    OLED_Command_160128RGB(0x06);
    OLED_Data_160128RGB(0x01); // Display On (0x00/0x01)
    OLED_Command_160128RGB(0x05); // Disable Power Save Mode
    OLED_Data_160128RGB(0x00); // Set All Internal Register Value as Normal Mode
    OLED_Command_160128RGB(0x15);
    OLED_Data_160128RGB(0x00); // Set RGB Interface Polarity as Active Low
    OLED_SetColumnAddress_160128RGB(0, 159);
    OLED_SetRowAddress_160128RGB(0, 127);
}


/*********************************/
/****** LOW LEVEL FUNCTIONS ******/
/************* START *************/
/*********************************/

// send command to OLED
void NhdOledDisplay::OLED_Command_160128RGB(unsigned char c)
{
    unsigned char i;
    unsigned char mask = 0x80;

    digitalWrite(CS_PIN, LOW);
    digitalWrite(RS_PIN, LOW);
    for(i=0;i<8;i++)
    {
    	digitalWrite(SCL_PIN, LOW);
        if((c & mask) >> 7 == 1)
        {
        	digitalWrite(SDI_PIN, HIGH);
        }
        else
        {
        	digitalWrite(SDI_PIN, LOW);
        }
            digitalWrite(SCL_PIN, HIGH);
            c = c << 1;
        }
        digitalWrite(CS_PIN, HIGH);
}

// send data to OLED
void NhdOledDisplay::OLED_Data_160128RGB(unsigned char d)
{
    unsigned char i;
    unsigned char mask = 0x80;

    digitalWrite(CS_PIN, LOW);
    digitalWrite(RS_PIN, HIGH);
    for(i=0;i<8;i++)
    {
    	digitalWrite(SCL_PIN, LOW);
        if((d & mask) >> 7 == 1)
        {
        	digitalWrite(SDI_PIN, HIGH);
        }
        else
        {
            digitalWrite(SDI_PIN, LOW);
        }
            digitalWrite(SCL_PIN, HIGH);
            d = d << 1;
     }
     digitalWrite(CS_PIN, HIGH);
}

// serial write for pixel data
void NhdOledDisplay::OLED_SerialPixelData_160128RGB(unsigned char d)
{
    unsigned char i;
    unsigned char mask = 0x80;
    digitalWrite(CS_PIN, LOW);
    digitalWrite(RS_PIN, HIGH);
    for(i=0;i<6;i++)
    {
        digitalWrite(SCL_PIN, LOW);
        if((d & mask) >> 7 == 1)
        {
            digitalWrite(SDI_PIN, HIGH);
        }
        else
        {
            digitalWrite(SDI_PIN, LOW);
        }
        digitalWrite(SCL_PIN, HIGH);
        d = d << 1;
    }
    digitalWrite(CS_PIN, HIGH);
}

// set column address start + end
void NhdOledDisplay::OLED_SetColumnAddress_160128RGB(unsigned char x_start, unsigned char x_end)
{
    OLED_Command_160128RGB(0x17);
    OLED_Data_160128RGB(x_start);
    OLED_Command_160128RGB(0x18);
    OLED_Data_160128RGB(x_end);
}

// set row address start + end
void NhdOledDisplay::OLED_SetRowAddress_160128RGB(unsigned char y_start, unsigned char y_end)
{
    OLED_Command_160128RGB(0x19);
    OLED_Data_160128RGB(y_start);
    OLED_Command_160128RGB(0x1A);
    OLED_Data_160128RGB(y_end);
}

// write to RAM command
void NhdOledDisplay::OLED_WriteMemoryStart_160128RGB(void)
{
    OLED_Command_160128RGB(0x22);
}

// write one pixel of a given color
void NhdOledDisplay::OLED_Pixel_160128RGB(unsigned long color)
{
    OLED_SerialPixelData_160128RGB((color>>16));
    OLED_SerialPixelData_160128RGB((color>>8));
    OLED_SerialPixelData_160128RGB(color);
}

// set x,y address
void NhdOledDisplay::OLED_SetPosition_160128RGB(unsigned char x_pos, unsigned char y_pos)
{
    OLED_Command_160128RGB(0x20);
    OLED_Data_160128RGB(x_pos);
    OLED_Command_160128RGB(0x21);
    OLED_Data_160128RGB(y_pos);
}

// fill screen with a given color
void NhdOledDisplay::fillScreen(unsigned long color)
{
    unsigned int i;
    OLED_SetPosition_160128RGB(0,0);
    OLED_WriteMemoryStart_160128RGB();
    for(i=0;i<(height*width);i++)
    {
        OLED_Pixel_160128RGB(color);
    }
}

/*===============================*/
/*===== LOW LEVEL FUNCTIONS =====*/
/*============= END =============*/
/*===============================*/


/*********************************/
/***** HIGH LEVEL FUNCTIONS ******/
/************ START **************/
/*********************************/

// print an image
void NhdOledDisplay::printImage(unsigned char x_pos, unsigned char y_pos, const unsigned char* image, int imageWidth, int imageHeight)
{
    int i, j;
    unsigned int incr = 0;

    for(i=0;i<imageHeight;i++)
    {
        OLED_SetPosition_160128RGB(x_pos,y_pos+i);
        OLED_WriteMemoryStart_160128RGB();
        for(j=0;j<(imageWidth*3);j+=3)
        {
            OLED_SerialPixelData_160128RGB(*(image+j+incr));
            OLED_SerialPixelData_160128RGB(*(image+j+incr+1));
            OLED_SerialPixelData_160128RGB(*(image+j+incr+2));
        }
        incr += (imageWidth*3);
    }
}

void NhdOledDisplay::drawButton(unsigned char x_pos, unsigned char y_pos, uint width, uint height, const char text[], unsigned long textColor, unsigned long buttonColor)
{
	uint buttonHeight = height;
	if(height < CHAR_HEIGHT+2)
	{
		buttonHeight = CHAR_HEIGHT+2;
	}
	drawRectange(x_pos, y_pos, width, buttonHeight, buttonColor);
	printTextCentered((y_pos+(buttonHeight-CHAR_HEIGHT)/2), (x_pos+(width/2)), text, textColor, buttonColor);
}

void NhdOledDisplay::printText(unsigned char x_pos, unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor)
{
	for(uint i=0;i<strlen(text);i++)
	{
		OLED_Text_160128RGB(x_pos+(i*6), y_pos, int(text[i]), textColor, backgroundColor);
	}
}

void NhdOledDisplay::printTextCentered(unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor)
{
	printTextCentered(y_pos, (width/2), text, textColor, backgroundColor);
}

void NhdOledDisplay::printTextCentered(unsigned char y_pos, unsigned char center, const char text[], unsigned long textColor, unsigned long backgroundColor)
{
	unsigned char x_pos = 0;

	uint numOfPixel = getTextPixels(text, 5, 1);

	x_pos = center - numOfPixel / 2;
	x_pos -= 2;

	printText(x_pos, y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printText2x(unsigned char x_pos, unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor)
{
	for(uint i=0;i<strlen(text);i++)
	{
		OLED_Text2x_160128RGB(x_pos+(i*12), y_pos, int(text[i]), textColor, backgroundColor);
	}
}

void NhdOledDisplay::printText2xCentered(unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor)
{
	printText2xCentered(y_pos, (width/2), text, textColor, backgroundColor);
}

void NhdOledDisplay::printText2xCentered(unsigned char y_pos, unsigned char center, const char text[], unsigned long textColor, unsigned long backgroundColor)
{
	unsigned char x_pos = 0;

	uint numOfPixel = getTextPixels(text, 10, 2);

	x_pos = center - numOfPixel / 2;
	x_pos -= 5;

	printText2x(x_pos, y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printInt(unsigned char x_pos, unsigned char y_pos, int number, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	sprintf(text, "%d", number);
	printText(x_pos, y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printIntCentered(unsigned char y_pos, int number, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	sprintf(text, "%d", number);
	printTextCentered(y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printIntCentered(unsigned char y_pos, unsigned char center, int number, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	sprintf(text, "%d", number);
	printTextCentered(y_pos, center, text, textColor, backgroundColor);
}

void NhdOledDisplay::printInt2x(unsigned char x_pos, unsigned char y_pos, int number, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	sprintf(text, "%d", number);
	printText2x(x_pos, y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printInt2xCentered(unsigned char y_pos, int number, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	sprintf(text, "%d", number);
	printText2xCentered(y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printInt2xCentered(unsigned char y_pos, unsigned char center, int number, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	sprintf(text, "%d", number);
	printText2xCentered(y_pos, center, text, textColor, backgroundColor);
}

void NhdOledDisplay::printFloat(unsigned char x_pos, unsigned char y_pos, float number, int precision, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	floatToString(number, precision, text);
	printText(x_pos, y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printFloatCentered(unsigned char y_pos, float number, int precision, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	floatToString(number, precision, text);
	printTextCentered(y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printFloatCentered(unsigned char y_pos, unsigned char center, float number, int precision, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	floatToString(number, precision, text);
	printTextCentered(y_pos, center, text, textColor, backgroundColor);
}

void NhdOledDisplay::printFloat2x(unsigned char x_pos, unsigned char y_pos, float number, int precision, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	floatToString(number, precision, text);
	printText2x(x_pos, y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printFloat2xCentered(unsigned char y_pos, float number, int precision, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	floatToString(number, precision, text);
	printText2xCentered(y_pos, text, textColor, backgroundColor);
}

void NhdOledDisplay::printFloat2xCentered(unsigned char y_pos, unsigned char center, float number, int precision, unsigned long textColor, unsigned long backgroundColor)
{
	char text[] = "";
	floatToString(number, precision, text);
	printText2xCentered(y_pos, center, text, textColor, backgroundColor);
}

void NhdOledDisplay::drawHLine(unsigned char x_pos_start, unsigned char x_pos_stop, unsigned char y_pos, unsigned long color)
{
	unsigned char lower = x_pos_start;
	unsigned char upper = x_pos_stop;
	if(x_pos_start > x_pos_stop)
	{
		lower = x_pos_stop;
		upper = x_pos_start;
	}
	if(lower < 0)
	{
		lower = 0;
	}
	if(upper > width)
	{
		upper = width;
	}
	// draw the line!
	for(unsigned char i=lower;i<=upper;i++)
	{
        OLED_SetPosition_160128RGB(i,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        OLED_Pixel_160128RGB(color);
	}
}

void NhdOledDisplay::drawVLine(unsigned char x_pos, unsigned char y_pos_start, unsigned char y_pos_stop, unsigned long color)
{
	unsigned char lower = y_pos_start;
	unsigned char upper = y_pos_stop;
	if(y_pos_start > y_pos_stop)
	{
		lower = y_pos_stop;
		upper = y_pos_start;
	}
	if(lower < 0)
	{
		lower = 0;
	}
	if(upper > height)
	{
		upper = height;
	}
	// draw the line!
	for(unsigned char i=lower;i<=upper;i++)
	{
        OLED_SetPosition_160128RGB(x_pos,i);
        OLED_WriteMemoryStart_160128RGB();
        OLED_Pixel_160128RGB(color);
	}
}

void NhdOledDisplay::drawRectange(unsigned char x_pos, unsigned char y_pos, uint width, uint height, unsigned long color)
{
	for(uint i=y_pos;i<(y_pos+height);i++)
	{
		drawHLine(x_pos, (x_pos+width), i, color);
	}
}

unsigned int NhdOledDisplay::getWidth()
{
	return width;
}

unsigned int NhdOledDisplay::getHeight()
{
	return height;
}

// function to show text
void NhdOledDisplay::OLED_Text_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)
{
    int i;
    int count;
    unsigned char mask = 0x80;

    for(i=0;i<CHAR_HEIGHT;i++)     // each character is 8 pixels tall
    {
        OLED_SetPosition_160128RGB(x_pos,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<CHAR_WIDTH;count++)    // each character is 5 pixels wide
        {
            if((Ascii_1[letter][count] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
        }
        y_pos++;
        mask = mask >> 1;
    }
}

// function to show text (2x size)
void NhdOledDisplay::OLED_Text2x_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)
{
    int i;
    int count;
    unsigned char mask = 0x80;

    for(i=1;i<=(CHAR_HEIGHT*2);i++)     // each character is 16 pixels tall
    {
        OLED_SetPosition_160128RGB(x_pos,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<(CHAR_WIDTH*2);count++)    // each character is 10 pixels wide
        {
            if((Ascii_1[letter][(count/2)] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
        }
        y_pos++;
        if((i%2)==0)
        {
            mask = mask >> 1;
        }
    }
}

uint NhdOledDisplay::getTextPixels(const char text[], uint charWidth, uint spaceWidth)
{
	uint numOfChars = strlen(text) - 1;
	uint numOfSpaces = 0;
	if(numOfChars > 1)
	{
		numOfSpaces = numOfChars - 1;
	}
	return numOfChars * charWidth + numOfSpaces * spaceWidth;
}

void NhdOledDisplay::floatToString(float number, int precision, char* string)
{
	uint tempInt = int(number);
	int digitsBeforePoint = 0;
	while(tempInt > 0)
	{
		digitsBeforePoint++;
		tempInt /= 10;
	}
	dtostrf(number,(digitsBeforePoint+1+precision), precision, string);
}

// function to show color spectrum
void NhdOledDisplay::OLED_Spectrum_160128RGB(void)
{
    unsigned char i, j;
    unsigned char blue, green, red;

    OLED_SetPosition_160128RGB(0,0);
    OLED_WriteMemoryStart_160128RGB();
    for(i=0;i<160;i++)
    {
        OLED_Pixel_160128RGB(WHITE);
    }
    OLED_SetPosition_160128RGB(0,1);
    OLED_WriteMemoryStart_160128RGB();
    for(i=0;i<160;i++)
    {
        OLED_Pixel_160128RGB(WHITE);
    }
    for(i=0;i<40;i++)
    {
        blue = 0x00;
        green = 0x00;
        red = 0xFF;
        OLED_SetPosition_160128RGB(0,(2+i));
        OLED_WriteMemoryStart_160128RGB();
        OLED_Pixel_160128RGB(WHITE);
        OLED_Pixel_160128RGB(WHITE);
        for(j=0;j<26;j++)
        {
            OLED_Data_160128RGB(blue);
            OLED_Data_160128RGB(green);
            OLED_Data_160128RGB(red);
            green += 9;
        }
        for(j=0;j<26;j++)
        {
            OLED_Data_160128RGB(blue);
            OLED_Data_160128RGB(green);
            OLED_Data_160128RGB(red);
            red -= 9;
        }
        for(j=0;j<26;j++)
        {
            OLED_Data_160128RGB(blue);
            OLED_Data_160128RGB(green);
            OLED_Data_160128RGB(red);
            blue += 9;
        }
        for(j=0;j<26;j++)
        {
            OLED_Data_160128RGB(blue);
            OLED_Data_160128RGB(green);
            OLED_Data_160128RGB(red);
            green -= 9;
        }
        for(j=0;j<26;j++)
        {
            OLED_Data_160128RGB(blue);
            OLED_Data_160128RGB(green);
            OLED_Data_160128RGB(red);
            red += 9;
        }
        for(j=0;j<26;j++)
        {
            OLED_Data_160128RGB(blue);
            OLED_Data_160128RGB(green);
            OLED_Data_160128RGB(red);
            blue -= 9;
        }
        OLED_Pixel_160128RGB(WHITE);
        OLED_Pixel_160128RGB(WHITE);
    }

    OLED_SetPosition_160128RGB(0,42);
    OLED_WriteMemoryStart_160128RGB();
    for(i=0;i<160;i++)
    {
        OLED_Pixel_160128RGB(WHITE);
    }
    OLED_SetPosition_160128RGB(0,43);
    OLED_WriteMemoryStart_160128RGB();
    for(i=0;i<160;i++)
    {
        OLED_Pixel_160128RGB(WHITE);
    }
}

/*===============================*/
/*==== HIGH LEVEL FUNCTIONS =====*/
/*============= END =============*/
/*===============================*/





