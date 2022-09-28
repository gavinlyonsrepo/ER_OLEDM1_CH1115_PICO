[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

![ OLED ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/oled.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Output](#output)
  * [Hardware](#hardware)
  * [Software](#software)
  
Overview
--------------------
* Name : ER_OLEDM1_CH1115_PICO
* Title : Library to support the ER-OLEDM1.09-1 128X64 OLED Display Module driven by the CH1115 controller 

* Description : 

1. Raspberry pi PICO RP2040 library.      
2. Invert colour, vertical rotate, sleep, fade effect, horizontal scroll and contrast control  functions supported.
3. 5 ASCII fonts included.
4. Graphics support included.
5. Multi-buffer Mode
6. Bitmaps supported.
7. Hardware SPI.

* Author: Gavin Lyons
* Developed on
	1. Raspberry pi PICO RP2040
	2. SDK C++ compiler G++ for arm-none-eabi
	3. CMAKE , VScode
* Ported from  [arduino library](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115)

Output
-----------------------------

Output Screenshots, From left to right, top to bottom.

1. Full screen bitmap displayed 
2. Multi buffer mode screen divided into two horizontal buffers
3. Multi buffer mode screen divided into vertical buffers, clock demo.
4. Different size and type of fonts 
5. Available ASCII font printed out 0-127
6. Extended ASCII font printed out 128-255  
7. Font 1-4 
8. Font 5 

![ output ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/output.jpg)
![ output ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_RPI/blob/main/extras/image/fontpic.jpg)


Hardware
----------------------------

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

Software
-------------------------

*SPI*

Hardware SPI. The hardware SPI speed is set at 1MHz you can increase this if necessary by changing OLEDbegin function.
Sp10 is used in exmaple files but can be changed by passing a different SPI channel. 

*buffers*

The screen can be divided into different sections with a shared buffer or the entire screen can be allocated to the a single buffer see  example files for details.

*fonts*

There are five fonts.
A print class is available to print out most passed data types.
The fonts 1-4 are a byte high(at text size 1) scale-able fonts, columns of padding added by SW.
Font 5 is a special large font but it is numbers only and cannot be scaled(just one size).  
Font 5 will print just numbers + semi-colons ,  if you print a float using print command
it will place a space and use a circle for a decimal point.

Font data table: 

| Font num | Font enum name | Font size xbyy |  ASCII range | Size in bytes |
| ------ | ------ | ------ | ------ |  ------ | 
| 1 | CH1115Font_Default | 5x8 | ASCII 0 - 0xFF, Full Extended  | 1275 |
| 2 | CH1115Font_Thick   | 7x8 |  ASCII  0x20 - 0x5A, no lowercase letters | 406 | 
| 3 | CH1115Font_Seven_Seg  | 4x8 | ASCII  0x20 - 0x7A | 360 |
| 4 | CH1115Font_Wide | 8x8 |  ASCII 0x20 - 0x5A, no lowercase letters| 464 |
| 5 | CH1115Font_Bignum | 16x32 | ASCII 0x30-0x3A ,Numbers + : . only | 704 |


*font mods*

The default ASCII font (font 1) is an extended font, 0-255 characters.
If you do not need characters 127-255 and wish to save memory space:
In library header file ER_OLEDM1_CH1115_font.h in the USER FONT OPTION TWO section
Simply comment this define out. 

1. UC_FONT_MOD_TWO (save 640 bytes) extended ASCII 127-255

You can also remove the first 30 characters of default font if not needed but user will need to change  offset in setFontNum function. This will save a further 150 bytes.

*bitmaps*

There is a few different ways of displaying bitmaps, 

| Num | Method | Buffer mode |   Data addressing | Note |
| ------ | ------ | ------ | ------ |  ------ |  
| 1 | OLEDBitmap() | any  | Vertical |  Writes directly to screen , no buffer used. | 
| 2 | OLEDBuffer() | Multi or Single |  Vertical  |  Mostly for internal use ... mostly | 
| 3 | Multi buffer init  | Multibuffer | Vertical  |  Can be used when initialising a MB | 
| 4 | Single buffer init | Single | Vertical  |  Can be used when initialising SB | 
| 5 | drawBitmap() | Multi or Single | Vertical | default,  setDrawBitmapAddr(true) | 
| 6 | drawBitmap() | Multi or Single |  Horizontal | setDrawBitmapAddr(false) |

See the bitmap example file for more details on each method. Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) , Bitmaps  should be defined in the program memory and buffers in the data memory, for methods 3 & 4 buffers can be initialised with bitmap data.

*User adjustments*

When the user calls OLEDbegin() to start OLED they can specify a contrast setting from 0x00 to 0xFF. Datasheet says 0x80 is default. User can also change contrast on the fly.
Screen can be disabled to enter a sleep type mode where OLED draws 500uA.
Screen pixel colour can be inverted and also screen can be vertically rotated. 

There is a "fade or breath display effect". Whose parameters(time brightness) can be adjusted by passing data to function see "OLEDfadeEffect" function header  in .cpp and datasheet for details.
default is 0x81.

There is a  Horizontal scroll effect. Whose parameters: Time-interval , direction , mode,
can be adjusted by passing data to function see "OLEDscrollSetup" function header in .cpp and datasheet for details. defaults are : 6 frames , right , continuous mode.

Files
-------------------

X = ER_OLEDM1_CH1115 in tables below

| Src Files | Description  |
| ------ | ------ |
| X.h | library header file  |
| X.cpp |  library  source file  |
| X_graphics.h | graphics header file |
| X_graphics.cpp |  graphics source file |
| X_graphics_font.h |  font data file |
| X_print.h | used for printing data types |
| X_print.cpp |  used for printing data types |

The example files are in example folder copy the one you want
into the src folder and replace the main.cpp that is there  
by default this is the Hello world one.

| Examples files ino  | Description |
| ------ | ------ | 
| X_HELLO | Hello world , Basic usage | 
| X_MBUF | Shows use of multi buffer mode | 
| X_CLOCK | Shows "clock demo" | 
| X_MISC | Fonts + graphics & misc functions, rotate , scroll,  etc | 
| X_BITMAP | Shows use of bitmaps  | 





