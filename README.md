[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

# ER_OLEDM1_CH1115_PICO

![ OLED](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/oled.jpg)

## Table of contents


  * [Overview](#overview)
  * [Output](#output)
  * [Hardware](#hardware)
  * [Software](#software)
	* [API Documentation](#api-Documentation)
	* [SPI](#spi)
	* [Fonts](#fonts)
	* [Bitmaps](#bitmaps)
  * [File system](#file-system)
  
## Overview

* Name : ER_OLEDM1_CH1115_PICO
* Title : Library to support the ER-OLEDM1.09-1 128X64 OLED Display Module driven by the CH1115 controller 

* Description : 

1. Raspberry pi PICO RP2040 library.      
2. Invert colour, vertical rotate, sleep, fade effect, horizontal scroll and contrast control  functions supported.
3. 10 ASCII fonts included.
4. Graphics support included.
5. Buffer Mode
6. Bitmaps supported.
7. Hardware SPI.
8. Polymorphic print class included to print many data types.

* Author: Gavin Lyons
* Developed on
	1. Raspberry pi PICO RP2040
	2. SDK C++ compiler G++ for arm-none-eabi
	3. CMAKE , VScode
* Ported from  my [arduino library](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115)

## Output

Output Screenshots.

![ p ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_PICO/blob/main/extra/image/all.jpg)

## Hardware

CH1115 is a single-chip CMOS OLED driver with controller for organic light emitting diode dot-matrix graphic display system. CH1115 consists of 128 segments, 64 commons that can support a maximum display resolution of 128 X 64. It is designed for Common Cathode type OLED panel. ER-OLEDM1.09-1W-SPI is a White 1.09" OLED Display Panel with Breakout Board. This module is a combination of the two.(controller and OLED)

| pin no  | pin name | pin desc |
|---|---|---|
| 1 | Gnd | Ground |
| 2 | VCC | voltage supply |
| 3 | SCL | Serial clock input |
| 4 | SDA | Serial data input |
| 5 | RES | This pin is reset signal input. When the pin is low, initialization of the chip is executed. |
| 6 | DC | This pin is Data or Command control pin. |
| 7 | CS | This pin is chip select input. The chip is enabled for MCU comms  when CS is pulled low|
 
This wiring Diagram from the manufacturer datasheet showing hardware setup connected to a 3.3 volt system MCU.

![ wiring ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/wiring.jpg)

## Software


### API Documentation

The Software is commented mostly for "doxygen" and if users uses "doxygen" software
an API document  can be generated. A Doxyfile is in "doc" sub folder in repository.

### SPI

Hardware SPI. The hardware SPI speed is set at 8MHz you can increase this if necessary by changing OLEDbegin method arguments.
Spi0 is used in example files but can be changed by passing a different SPI channel. 

### Fonts

There are 10 fonts packaged with library. Fonts can be easily added or removed by user.
All the Font data is in file CH1115_OLED_font.cpp and CH1115_OLED_font.hpp

Font data table: 

| num | Font pointer name | character size XxY |  ASCII range | Size in bytes |
| ------ | ------ | ------ | ------ |  ------ | 
| 1 | pFontDefault | 6x8 |  0 - 0xFE, Full Extended  | 1534 |
| 2 | pFontWide | 9x8 | 0x20 - 0x5A, NO lowercase letters | 535 |
| 3 | pFontPico | 4x6 | 0x20 - 0x7E  | 289 | 
| 4 | pFontSinclairS  | 8x8 | 0x20 - 0x7E | 764 |
| 5 | pFontMega | 16x16 | 0x20 - 0x7E | 3044 |
| 6 | pFontArialBold  | 16x16 | 0x20 - 0x7E |  3044 |
| 7 | pFontHallfetica | 16x16 | 0x20 - 0x7E | 3044 |
| 8 | pFontArialRound| 16x24 | 0x20 - 0x7E | 4564 |
| 9 | pFontGroTesk | 16x32 | 0x20 - 0x7A |  5828 |
| 10 | pFontSixteenSeg | 32x48 | 0x2D-0x3A , 0-10  :  .  / - only | 2692 |

Font size in bytes = ((X * (Y/8)) * numberOfCharacters) + (4*ControlByte)

| Font class Function | Notes |
| ------ | ------ | 
| writeChar| draws single character |
| writeCharString | draws character array |
| print | Polymorphic print class which will print out many data types |

These methods return an error code in event of an error such as, ASCII character outside chosen fonts range, character out of screen bounds and invalid character array pointer object.

**Remove a font**

To remove an unwanted font from project simply comment out or delete.

1. The Font data in CH1115_OLED_font.cpp file
2. The pointer to font at bottom of CH1115_OLED_font.cpp file
3. The associated extern pointer declaration in the CH1115_OLED_font.hpp file

**Adding a new font**

1. Add the Font data in CH1115_OLED_font.cpp file
2. Add a pointer to font at bottom of CH1115_OLED_font.cpp file
3. Add an associated extern pointer declaration in the CH1115_OLED_font.hpp file

The new ASCII font must have following font structure.
First 4 bytes are control bytes followed by vertically addressed font data.

```
// An 4 by 8 character size font starting at 
// ASCII offset 0x30 in ASCII table with 0x02 characters in font. 
// 0 and 1 
static const uint8_t FontBinaryExample[] =
{
0x04, 0x08, 0x30, 0x02,   // x-size, y-size, offset, total characters
(data),(data),(data),(data) // font data '0'
(data),(data),(data),(data) // font data '1'
}
```

Some of the fonts packaged with library came from [URL](http://rinkydinkelectronics.com/).
If user has picture of a font like so.

![ font ](https://github.com/gavinlyonsrepo/SSD1306_OLED_PICO/blob/main/extra/image/hallfetica_normal.png)

There is a monochrome font maker there at [URL](http://rinkydinkelectronics.com/t_make_font_file_mono.php)

### Bitmaps

OLEDBitmap function will return an error if : The Bitmap is completely off screen , Invalid Bitmap pointer object, bitmap bigger than screen , bitmap bigger/smaller than provided width and height calculation ( This helps prevents buffer overflow). A horizontal addressed Bitmap's width MUST be divisible by 8. eg, for a bitmap with width=88 and height=48. Bitmap excepted size = (88/8) * 48 = 528 bytes.

Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) 
See example file "_BITMAP" for more details.

### User adjustments

When the user calls OLEDinit() to start OLED they can specify a contrast setting from 0x00 to 0xFF. Datasheet says 0x80 is default. User can also change contrast on the fly.
Screen can be disabled to enter a sleep type mode where OLED draws 500uA.
Screen pixel colour can be inverted and also screen can be vertically rotated. 

There is a "fade or breath display effect". Whose parameters(time brightness) can be adjusted by passing data to function see "OLEDfadeEffect" function header  in .cpp and datasheet for details.
default is 0x81.

There is a  Horizontal scroll effect. Whose parameters: Time-interval , direction , mode,
can be adjusted by passing data to function see "OLEDscrollSetup" function header in .cpp and datasheet for details. defaults are : 6 frames , right , continuous mode.

## Files system

X = ER_OLEDM1_CH1115 in tables below

| Src Files | Description  |
| ------ | ------ |
| X.hpp | library header file  |
| X.cpp |  library  source file  |
| X_graphics.hpp | graphics header file |
| X_graphics.cpp |  graphics source file |
| X_font.hpp |  font header file |
| X_font.cpp |  font data file |
| X_print.hpp | used for printing data types |
| X_print.cpp |  used for printing data types |

The example files are in example folder.
To build the one you want, edit the Cmaketxt file 
add_executable(${PROJECT_NAME} section, comment in one example file path and one only.
The default is the Hello world one.

| Examples files main.cpp  | Description |
| ------ | ------ | 
| X_HELLO | Hello world , Basic usage | 
| X_FPS_FUNCTIONS | FPS test & misc functions, rotate , scroll,  etc | 
| X_TEXT_GRAPHICS  | Fonts + graphics  |
| X_BITMAP | Shows use of bitmaps methods  | 
