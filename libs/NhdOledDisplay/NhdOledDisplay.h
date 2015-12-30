/*
 * NhdOledDisplay.h
 *
 *  Created on: 25.12.2015
 *      Author: frehnerp
 */

#ifndef NHDOLEDDISPLAY_H_
#define NHDOLEDDISPLAY_H_

#include <Arduino.h>

class NhdOledDisplay {
public:
	NhdOledDisplay(unsigned int displayWidth,
			       unsigned int displayHeight,
			       uint8_t SDI,
			       uint8_t SCL,
				   uint8_t RS,
				   uint8_t RES,
				   uint8_t CS,
				   uint8_t PS);
	virtual ~NhdOledDisplay();

	void init();

	// high level functions
	void printImage(unsigned char x_pos, unsigned char y_pos, const unsigned char* image, int imageWidth, int imageHeight);
	void printText(unsigned char x_pos, unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor);
	void printTextCentered(unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor);
	void printText2x(unsigned char x_pos, unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor);
	void printText2xCentered(unsigned char y_pos, const char text[], unsigned long textColor, unsigned long backgroundColor);
	void drawHLine(unsigned char x_pos_start, unsigned char x_pos_stop, unsigned char y_pos, unsigned long color);
	void drawVLine(unsigned char x_pos, unsigned char y_pos_start, unsigned char y_pos_stop, unsigned long color);
	void OLED_Spectrum_160128RGB(void);
	void fillScreen(unsigned long color);

	// getters
	unsigned int getWidth();
	unsigned int getHeight();

	// colors
	unsigned long RED;
	unsigned long GREEN;
	unsigned long BLUE;
	unsigned long WHITE;
	unsigned long BLACK;
	unsigned long YELLOW;

private:
	unsigned int width;
	unsigned int height;

	uint8_t SDI_PIN;
	uint8_t SCL_PIN;
	uint8_t RS_PIN;
	uint8_t RES_PIN;
	uint8_t CS_PIN;
	uint8_t PS_PIN;

	void pinConfiguration();
	void OLED_Init_160128RGB(void);

	// low level functions
	void OLED_Command_160128RGB(unsigned char c);
	void OLED_Data_160128RGB(unsigned char d);
	void OLED_SerialPixelData_160128RGB(unsigned char d);
	void OLED_SetColumnAddress_160128RGB(unsigned char x_start, unsigned char x_end);
	void OLED_SetRowAddress_160128RGB(unsigned char y_start, unsigned char y_end);
	void OLED_WriteMemoryStart_160128RGB(void);
	void OLED_Pixel_160128RGB(unsigned long color);
	void OLED_SetPosition_160128RGB(unsigned char x_pos, unsigned char y_pos);

	void OLED_Text_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor);
	void OLED_Text2x_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor);

};

#endif /* NHDOLEDDISPLAY_H_ */