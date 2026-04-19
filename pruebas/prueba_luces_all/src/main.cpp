#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define CS_PIN 10
#define NUM_PANELS 3

int v = 0;

Max72xxPanel matrix = Max72xxPanel(CS_PIN, NUM_PANELS, 1);

void setup() {  
  matrix.setIntensity(15);    
  matrix.setRotation(3);
}

void todo(int i) {
  // Prueba 1: Todo rojo
  matrix.fillScreen(i);
  matrix.write();
  // delay(500);  
}

void un_px(int i, char p){
  // matrix.drawCircle(3,3,2,1);
  
  if(p == 'a'){
    matrix.drawChar(v,16,'P',1,0,1);
  }
  if(p == 'b'){
    matrix.drawChar(v,8,'P',1,0,1);
  }
  if(p == 'c'){
    matrix.drawChar(v,0,'P',1,0,1);
  }
  
  matrix.write();
  // delay(100);
}

void loop() {
  
  // todo(1);
  todo(0);
  un_px(v,'a');
  // un_px(v, 'b');
  // un_px(v, 'c');
  v++;

  if(v == 16){
    v=0;
  }
  delay(100);
    
}



