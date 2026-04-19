/************************************************* *************************************************
* OPEN-SMART LED Maxtrix sketch for open-smart LED Matrix F3 or LED Matrix F5
https://www.aliexpress.com/store/product/8-x-8-Seamless-Cascadable-Red-LED-Dot-Matrix-F5-Display-Module-for-Arduino-Seamless-Cascadable/1199788_32784405370.html?spm=2114.12010615.0.0.KoeIDU
https://www.aliexpress.com/store/product/1-8-8-8-Red-LED-Dot-Matrix-Display-Module-for-Arduino-Cascadable-Square-with-SPI/1199788_32785050459.html?spm=2114.12010615.0.0.KoeIDU

www.dx.com/426816
www.dx.com/428619

* You can learn about how to display characters with multiple led matrix modules. 
*
************************************************** ************************************************** *****/#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

uint8_t pinCS = 4; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
uint8_t numberOfHorizontalDisplays = 3;//three LED Matrix module
uint8_t numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {

  matrix.setIntensity(2); // Use a value between 0 and 15 for brightness

// Adjust to your own needs

  matrix.setPosition(0, 2, 0);
  matrix.setPosition(1, 1, 0); 
  matrix.setPosition(2, 0, 0); 
 /* matrix.setPosition(3, 2, 0);
  matrix.setPosition(4, 1, 0); 
  matrix.setPosition(5, 0, 0);*/ 
//  matrix.setPosition(1, 0, 1); // The second display is at <1, 0>
//  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
//  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>
//  ...
 // matrix.setRotation(2, 2);    // The first display is position upside down
 matrix.setRotation(2);    // The same hold for the last display
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

