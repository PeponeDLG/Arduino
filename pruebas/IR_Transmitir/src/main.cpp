#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial irSerial(10, 11);  // (RX, TX) - RXD módulo → pin 11

/* Esto lo recepcioné con IR_leer
Código recibido: 04 FB 08 => encendido/apagado
Código recibido: 04 FB 02 => subir volumen
Código recibido: 04 FB 03 => bajar volumen
*/


// =====================================================
// CONFIGURACIÓN: Cambia este valor según lo que quieras enviar
// 0 = Encender/Apagar
// 1 = Subir Volumen  
// 2 = Bajar Volumen
// =====================================================
const int CODIGO_A_ENVIAR = 0;  // <--- CAMBIA AQUÍ (0, 1 o 2)
// =====================================================

// Los códigos capturados de tu mando TV
const byte CODIGO_POWER[]   = {0x04, 0xFB, 0x08};
const byte CODIGO_VOL_UP[]  = {0x04, 0xFB, 0x02};
const byte CODIGO_VOL_DOWN[] = {0x04, 0xFB, 0x03};

// Función para enviar un código IR de 3 bytes
void enviarIR(const byte codigo[3]) {
  // Construir payload de 5 bytes: Dirección (0xA1) + Comando (0xF1) + 3 bytes del código
  byte payload[5] = {0xA1, 0xF1, codigo[0], codigo[1], codigo[2]};
  
  // Enviar al módulo
  irSerial.write(payload, 5);
  
  // Mostrar en monitor serie lo que se envió
  Serial.print(F("[ENVIADO] "));
  for (int i = 0; i < 3; i++) {
    if (codigo[i] < 0x10) Serial.print("0");
    Serial.print(codigo[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  irSerial.begin(9600);
  
  Serial.println(F("=== EMISOR IR YS-IRTM ==="));
  Serial.print(F("Enviando cada 1 segundo: "));
  
  switch (CODIGO_A_ENVIAR) {
    case 0:
      Serial.println(F("ENCENDER/APAGAR"));
      break;
    case 1:
      Serial.println(F("SUBIR VOLUMEN"));
      break;
    case 2:
      Serial.println(F("BAJAR VOLUMEN"));
      break;
    default:
      Serial.println(F("VALOR INVÁLIDO (usa 0, 1 o 2)"));
      break;
  }
  Serial.println(F("========================"));
}

void loop() {
  // Seleccionar qué código enviar según la constante
  const byte* codigoAEmitir;
  int longitud;
  
  switch (CODIGO_A_ENVIAR) {
    case 0:
      codigoAEmitir = CODIGO_POWER;
      break;
    case 1:
      codigoAEmitir = CODIGO_VOL_UP;
      break;
    case 2:
      codigoAEmitir = CODIGO_VOL_DOWN;
      break;
    default:
      return;  // Si el valor es inválido, no hace nada
  }
  
  // Enviar el código IR
  enviarIR(codigoAEmitir);
  
  // Esperar 1 segundo
  delay(1000);
}

