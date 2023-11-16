#define LDR A0 // PIN ANALOGO PARA LDR.
#define DELAY_LDR 1500 // DELAY DE LDR en ms.

float LDR_VAL; // Variable auxiliar para lectura.

#include "Arduino.h" // Libreria de Arduino.
#include "LoRa_E32.h" // Libreria de Ebyte E32-433T30D.

// Construccion de objeto contenedor del Ebyte.
LoRa_E32 e32ttl100(&Serial1); // Se usa la dirección Serial1 (RX: 19 | TX: 18).

void setup() {
  Serial.begin(9600); // Se inicializa la comunicación serial con la computadora (para monitoreo).
  delay(500);
  // Inicializa los pines y el UART para el Ebyte.
  e32ttl100.begin();
}

void loop() {
  // Sección de Lectura de LDR -------------------------------
  Serial.print("Lectura de LDR\t: ");
  LDR_VAL = analogRead(LDR);
  Serial.println(String(LDR_VAL));
  Serial.print("Lectura en V\t: ");
  Serial.println(String(LDR_VAL * 4.882) + "mV");
  delay(DELAY_LDR);

  // Sección de envío de mensaje LoRa ------------------------
  // Envia el mensaje a todos los dispositivos en el canal de 433 MHz.
  ResponseStatus rs = e32ttl100.sendMessage(String(LDR_VAL) + " , " + String(LDR_VAL * 4.882) + "mV");
  // Revisa si existe algún problema.
  // Si la comunicación es exitosa muestra un "Success".
  Serial.print("Estado de envío:\t");
  Serial.println(rs.getResponseDescription());
}