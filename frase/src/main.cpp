#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define CS_PIN 10
#define NUM_PANELS 3  // Cambiar a 1 panel

Max72xxPanel matrix1 = Max72xxPanel(CS_PIN, 1,NUM_PANELS);

String palabra = "PEPONE DE LAS GALAXIAS :D";
int desplazamiento = 8;
int anchoTexto = 0;

void setup() {
    matrix1.setRotation(3);  // Rotación horizontal
    matrix1.fillScreen(0);
    
    anchoTexto = palabra.length() * 6;
}

void loop() {
    matrix1.fillScreen(0);
    matrix1.setCursor(desplazamiento, 0);
    matrix1.print(palabra);    
    matrix1.write();
    
    desplazamiento--;
    if (desplazamiento < -anchoTexto) desplazamiento = 8;
    
    delay(80);
}