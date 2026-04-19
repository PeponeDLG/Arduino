/************************************************* *************************************************
* OPEN-SMART LED Maxtrix sketch for 4 open-smart LED matrix 
www.aliexpress.com/store/product/1-8-8X8-Cascadable-Red-LED-Matrix-Display-Module-with-SPI-interface-for-Arduino/1199788_32524697496.html?spm=2114.12010615.0.0.hifC9x
www.dx.com/408734

* You can learn about how to display characters with multiple led matrix modules. 
*
************************************************** ************************************************** *****/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

uint8_t pinCS = 4; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
uint8_t numberOfHorizontalDisplays = 1;
uint8_t numberOfVerticalDisplays = 4;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {

  matrix.setIntensity(1); // Use a value between 0 and 15 for brightness

// Adjust to your own needs
  matrix.setPosition(0, 0, 3); // The first display is at <0, 3>
  matrix.setPosition(1, 0, 2); // The second display is at <0, 2>
  matrix.setPosition(2, 0, 1); // The third display is at <0, 1>
  matrix.setPosition(3, 0, 0); // And the last display is at <0, 0>
//  ...
//  matrix.setRotation(0, 2);    // The first display is position upside down
  matrix.setRotation(3);    // The same hold for the last display
  matrix.fillScreen(LOW);
 matrix.write();
 delay(400);
 matrix.print("OPEN");
 matrix.write();
 delay(2000);
}

void loop() {
  String tape = "OPEN-SMART";
  uint8_t wait = 120; // In milliseconds
  uint8_t spacer = 1;
  uint8_t width = 5 + spacer; // The font width is 5 pixels
  
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write(); // Send bitmap to display

    delay(wait);
  }
}

