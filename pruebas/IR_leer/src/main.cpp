#include <Arduino.h>
#include <SoftwareSerial.h>

/* Recepcionado del mando de la TV LG
Código recibido: 04 FB 08 => encendido/apagado
Código recibido: 04 FB 02 => subir volumen
Código recibido: 04 FB 03 => bajar volumen
*/


// Definimos los pines para el puerto serie virtual
// RX del software serial (conecta aquí el TXD del módulo)
// TX del software serial (conecta aquí el RXD del módulo, opcional)
const int rxPin = 10;  // Pin donde conectas TXD del módulo
const int txPin = 11;  // Pin donde conectas RXD del módulo

// Creamos el objeto SoftwareSerial
SoftwareSerial irSerial(rxPin, txPin);  // (RX, TX)

void setup() {
  // Iniciamos el monitor serie para ver resultados en el PC
  Serial.begin(9600);
  
  // Iniciamos la comunicación con el módulo YS-IRTM
  irSerial.begin(9600);
  
  Serial.println("=== Lector de Códigos IR ===");
  Serial.println("Conecta TXD del módulo al pin 10");
  Serial.println("Apunta tu mando y presiona botones...");
  Serial.println();
}

void loop() {
  // Verificamos si el módulo ha enviado datos
  if (irSerial.available() > 0) {
    // Pequeña pausa para que lleguen todos los bytes
    delay(100);
    
    Serial.print("Código recibido: ");
    
    // Leemos todos los bytes disponibles
    while (irSerial.available() > 0) {
      byte dato = irSerial.read();
      
      // Mostramos cada byte en hexadecimal
      if (dato < 0x10) {
        Serial.print("0");
      }
      Serial.print(dato, HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  
  delay(50);
}