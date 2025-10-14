/*  
!!!!!!!!!!!!!   CYD-noLVGL-template code    !!!!!!!!!!!!!!!!!!
    Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD): https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/cyd/
    2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display: https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/esp32-tft/
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <SPI.h>

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd/ or https://RandomNerdTutorials.com/esp32-tft/   */
#include <TFT_eSPI.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen
// Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();

#include "morse.h"

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 2

#define DITPERIOD 120 // period of dit, in milliseconds
#define LED PC13
#define LED_RED  4
#define LED_GREEN  16
#define LED_BLUE  17
#define PITCH 1200 // pitch in Hz of morse audio
#define AUDIO 26 

char cwchar = 'R';

void ditSpaces(int spaces) { // user specifies #dits to wait
for (int i=0; i<spaces; i++) // count the dits...
  delay(DITPERIOD); // no action, just mark time
}

void dit() {
digitalWrite(LED_GREEN,0); // turn on LED
tone(AUDIO,PITCH); // and turn on sound
ditSpaces(1);
digitalWrite(LED_GREEN,1); // turn off LED
noTone(AUDIO); // and turn off sound
ditSpaces(1); // space between code elements
}

void dah() {
digitalWrite(LED_GREEN,0); // turn on LED
tone(AUDIO,PITCH); // and turn on sound
ditSpaces(3); // length of dah = 3 dits
digitalWrite(LED_GREEN,1); // turn off LED
noTone(AUDIO); // and turn off sound
ditSpaces(1); // space between code elements
}

void characterSpace() {
ditSpaces(3); // space between characters = 3 dits
} 

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  digitalWrite(LED_GREEN,1); // turn off LED
  digitalWrite(LED_BLUE,1);  // turn off LED
  digitalWrite(LED_RED,1);   // turn off LED

   // Start the tft display
  tft.init();
  // Set the TFT display rotation in landscape mode
  tft.setRotation(3);

  // Clear the screen before writing to it
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  
  // Set X and Y coordinates for center of display
  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2;

  tft.drawCentreString(String(farnsworth[6].letter), centerX, centerY, 4);
}

void loop() {
  int x = farnsworth[6].bits; // get the bit pattern for the letter
  while (x>1) {               // stop when value is 1 (or less)
    if (x & 1) dit();         // right-most bit is 1, so dit
    else dah();               // right-most bit is 0, so dah
    x >>= 1;                  // shift bits right
  }
  characterSpace();           // add inter-character spacing
}

// dit(); 
// dah();
// dit(); 	// Send “R” as an example.
// delay(1000);

