
// ******************************
// Example file name : main.cpp :: folder ER_OLEDM1_CH1115_MBUF
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of mulitple buffers.  In this case: two, divided vertically.
// The user can also divide horizontally and create as many buffers as they want.
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
// GPIO 5-wire SPI interface
const uint mosi_pin = 19;
const uint sck_pin = 18;
const uint cs_pin = 17;
const uint res_pin = 3;
const uint dc_pin = 2;

ERMCH1115  myOLED(dc_pin, res_pin, cs_pin, sck_pin, mosi_pin); 

// vars for the test
static long previousMillis  = 0;
uint16_t count  = 0;
bool colour = 1;

// === Function prototypes ===
void display_Left(CH1115MultiBuffer* targetbuffer,long currentFramerate, int count);
void display_Right(CH1115MultiBuffer* targetbuffer);

// === Main ===
int main() {
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0);
  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.setFontNum(CH1115Font_Default);

  static long framerate = 0;
  uint8_t  screenBuffer[(MYOLEDWIDTH * (MYOLEDHEIGHT / 8)) / 2]; //(128 * 8)/2 = 512 bytes

  CH1115MultiBuffer left_side;
    // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&left_side, screenBuffer, MYOLEDWIDTH/2, MYOLEDHEIGHT, 0, 0);

  CH1115MultiBuffer right_side;
    // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&right_side, screenBuffer, MYOLEDWIDTH/2, MYOLEDHEIGHT, MYOLEDWIDTH/2, 0);

  while(1)
  {
    display_Left(&left_side, framerate, count);
    display_Right(&right_side);

    framerate++;
    count++;
    if (count == 5000)
    {
      myOLED.OLEDPowerDown(); // Switch off OLED when test over
      while(1){busy_wait_ms(100);} // wait here for ever
    }
  }
}
// === End of main ===

// === Function Space ===

// Function to display left hand side buffer
void display_Left(CH1115MultiBuffer* targetbuffer, long currentFramerate, int count)
{
  myOLED.ActiveBuffer = targetbuffer; // set target buffer object
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print("LHS Buffer");

  myOLED.setCursor(0, 10);
  myOLED.print("512 bytes");

  myOLED.setCursor(0, 20);
  myOLED.print("G Lyons");

  myOLED.setCursor(0, 30);
  myOLED.print(count);
  // Values to count frame rate per second
  static long lastFramerate = 0;
  static uint16_t fps;
  unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

  if (currentMillis  - previousMillis  >= 1000) {
    fps = currentFramerate - lastFramerate;
    lastFramerate = currentFramerate ;
    previousMillis  = currentMillis;
    colour = !colour;
  }

  myOLED.setCursor(0, 40);
  myOLED.print(fps);
  myOLED.print(" fps");
  myOLED.setCursor(0, 50);
  myOLED.print("Ver 1.0");
  myOLED.drawFastVLine(92, 0, 63, FOREGROUND);
  myOLED.OLEDupdate();
}

// Function to display right hand side buffer
void display_Right(CH1115MultiBuffer* targetbuffer)
{
  myOLED.ActiveBuffer = targetbuffer; // set target buffer object
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print("RHS buffer");

  myOLED.fillRect(0, 10, 20, 20-(count/200), colour);
  myOLED.fillCircle(40, 20, count/200, !colour);
  myOLED.drawRoundRect(10, 40, 40, 20, 10, FOREGROUND);

  myOLED.OLEDupdate();
}
//=== EOF ===