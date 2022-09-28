// ******************************
// Example file name : main.cpp :: folder = ER_OLEDM1_CH1115_HELLO
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of hello world
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_PICO
// *****************************

// === Libraries ===
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ch1115/ER_OLEDM1_CH1115.h"

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
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.setTextColor(FOREGROUND);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.OLEDFillScreen(0x00, 0);
    
  // Buffer setup  
  // Define a buffer to cover whole screen
  uint8_t  screenBuffer[MYOLEDWIDTH  * (MYOLEDHEIGHT / 8)]; // 1024 bytes = 128 * 64/8
  CH1115MultiBuffer myStruct;   // Declare a multibuffer struct 
  // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&myStruct, screenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);
  myOLED.ActiveBuffer = &myStruct;  // Assign struct to be the active buffer pointer
  myOLED.OLEDclearBuffer();   // Clear active buffer
  
  while (1)
  {
    myOLED.setCursor(20, 20);
    myOLED.print("Hello world");
    myOLED.OLEDupdate();  // Update  active buffer
    busy_wait_ms(5000);
  }
}
//=== end of main ===