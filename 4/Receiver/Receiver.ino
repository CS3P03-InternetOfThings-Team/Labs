#include "Arduino.h" // Libreria de Arduino
#include "LoRa_E32.h" // Libreria de Ebyte E32-433T30D

// Construcción de objeto contenedor del Ebyte.
LoRa_E32 e32ttl100(&Serial1); // Se usa la dirección Serial1 (RX: 19 | TX: 18)

void setup() {
  Serial.begin(9600); // Se inicializa la comunicación serial con la computadora (para monitoreo).
  delay(500);
  // Inicializa los pines y el UART para el Ebyte.

  e32ttl100.begin();

  // Mensaje de espera.
  Serial.println("Esperando mensajes LoRa en canal de 433MHz: ");
}

void loop() {
  // Verifica si hay buffer en el Ebyte.
  if (e32ttl100.available() > 1) {
    // Lee la cadena recibida.
    ResponseContainer rc = e32ttl100.receiveMessage(); // Objeto contenedor.

    if (rc.status.code != 1) { // Aviso en caso de error.
      rc.status.getResponseDescription();
    } else {
      // Imprime la data recibida.
      Serial.print("Mensaje recibido:\t");
      Serial.println(rc.data);
    }
  }
}