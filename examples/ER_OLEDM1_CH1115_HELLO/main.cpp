// ******************************
// Example file name : main.cpp :: folder = ER_OLEDM1_CH1115_HELLO
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of hello world
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_PICO
// *****************************

// === Libraries ===
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ch1115/ER_OLEDM1_CH1115.hpp"

// === Defines ===
#define OLEDcontrast 0x80 //Contrast 00 to FF , 0x80 is default. user adjust
#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128

// === Globals ===
const uint mosi_pin = 19;
const uint sck_pin = 18;
const uint cs_pin = 17;
const uint res_pin = 3;
const uint dc_pin = 2;

ERMCH1115  myOLED(dc_pin, res_pin, cs_pin, sck_pin, mosi_pin); 

// === Main ===
int main() {

  busy_wait_ms(50);
  
  // Screen Setup :
  // initialize the OLED , contrast , Spi interface , spi Baud rate in Khz
  myOLED.OLEDbegin(OLEDcontrast, spi0, 8000); 
  myOLED.setTextColor(FOREGROUND);
  myOLED.setFontNum(OLEDFontType_Default);
  myOLED.OLEDFillScreen(0x00, 0);
    
  // Buffer setup  
  // Define a buffer to cover whole screen
  uint8_t screenBuffer[MYOLEDWIDTH  * (MYOLEDHEIGHT / 8)]; // 1024 bytes = 128 * 64/8
  myOLED.OLEDbuffer = (uint8_t*) &screenBuffer;  // Assign the pointer to the buffer
  myOLED.OLEDclearBuffer();   // Clear  buffer
  
  while (1)
  {
    myOLED.setCursor(20, 20);
    myOLED.print("Hello world");
    myOLED.OLEDupdate();  // Update  active buffer
    busy_wait_ms(5000);
  }
}
//=== end of main ===