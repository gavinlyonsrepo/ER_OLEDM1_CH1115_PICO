/*!
   @file ER_OLEDM1_CH1115_graphics.hpp
   @brief ER_OLEDM1 OLED driven by CH1115 controller header file
   for the graphics based functions.ER_OLEDM1_CH1115_PICO
   @author  Gavin Lyons
*/

#pragma once

#include <cmath> // for abs function
#include <cstdio>
#include "ch1115/ER_OLEDM1_CH1115_Print.hpp"
#include "ch1115/ER_OLEDM1_CH1115_font.hpp"

#define OLEDCH1115swap(a, b) \
	{                        \
		int16_t t = a;       \
		a = b;               \
		b = t;               \
	}

/*! OLED rotate modes in degrees*/
enum  OLED_rotate_e : uint8_t
{
	OLED_Degrees_0 = 0, /**< No rotation 0 degrees*/
	OLED_Degrees_90,    /**< Rotation 90 degrees*/
	OLED_Degrees_180,   /**< Rotation 180 degrees*/
	OLED_Degrees_270   /**< Rotation 270 degrees*/
};

/*! @brief Font class to hold font data object  */
class ERMCH1115_OLEDFonts
{
public:
	ERMCH1115_OLEDFonts();
	~ERMCH1115_OLEDFonts(){};

	uint8_t setFont(const uint8_t *font);
	void setInvertFont(bool invertStatus);
	bool getInvertFont(void);

	const uint8_t *_FontSelect = pFontDefault; /**< Pointer to the active font,  Fonts Stored are Const */

protected:
	uint8_t _Font_X_Size = 0x06;  /**< Width Size of a Font character */
	uint8_t _Font_Y_Size = 0x08;  /**< Height Size of a Font character */
	uint8_t _FontOffset = 0x00;	  /**< Offset in the ASCII table 0x00 to 0xFF, where font begins */
	uint8_t _FontNumChars = 0xFE; /**< Number of characters in font 0x00 to 0xFE */
private:
	bool _FontInverted = false; /**< Is the font inverted , False = normal , true = inverted*/
};

/*! @brief Graphics class to hold graphic related functions */
class ERMCH1115_graphics : public ERMCH1115_OLEDFonts, public Print
{

public:
	ERMCH1115_graphics(int16_t w, int16_t h); // Constructor

	virtual size_t write(uint8_t);
	uint8_t writeChar(int16_t x, int16_t y, char value);
	uint8_t writeCharString(int16_t x, int16_t y, char *text);

	virtual void drawPixel(int16_t x, int16_t y, uint8_t color) = 0;

	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	void fillScreen(uint8_t color);

	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
						  uint8_t color);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
						  int16_t delta, uint8_t color);
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
					  int16_t x2, int16_t y2, uint8_t color);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
					  int16_t x2, int16_t y2, uint8_t color);
	void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
					   int16_t radius, uint8_t color);
	void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
					   int16_t radius, uint8_t color);

	void setDrawBitmapAddr(bool mode);
	uint8_t drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
					   int16_t w, int16_t h, uint8_t color, uint8_t bg, uint16_t sizeOfBitmap);

	void setCursor(int16_t x, int16_t y);
	void setTextWrap(bool w);

	void setRotation(OLED_rotate_e );
	OLED_rotate_e getRotation(void);

	int16_t height(void) const;
	int16_t width(void) const;

protected:
	const int16_t WIDTH;  /**< This is the 'raw' display w - never changes */
	const int16_t HEIGHT; /**< This is the 'raw' display h - never changes*/
	int16_t _width;		  /**< Display w as modified by current rotation*/
	int16_t _height;	  /**< Display h as modified by current rotation*/
	int16_t _cursor_x;	  /**< Current X co-ord cursor position */
	int16_t _cursor_y;	  /**< Current Y co-ord cursor position */

	uint8_t _rotation;	  /**< Holds current rotation 0-3 */
	bool _textwrap;		  /**< If set, 'wrap' text at right edge of display*/
	bool _drawBitmapAddr; /**< data addressing mode for method drawBitmap, True-vertical , false-horizontal */
	
	OLED_rotate_e OLED_rotate = OLED_Degrees_0; /**< Enum to hold rotation */
};
