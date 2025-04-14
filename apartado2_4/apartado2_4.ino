#include <stdint.h>
#include <DHT.h>

// === Configuración de pines ===
#define DHTPIN 23        // Pin conectado al sensor DHT11
#define DHTTYPE DHT11    // Especificamos el tipo de sensor

// Inicializamos el objeto del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Pines de los LEDs (tipo uint8_t por eficiencia)
uint8_t ledVerde = 2;
uint8_t ledAzul  = 4;
uint8_t ledRojo  = 18;

void setup() {

  Serial.begin(9600);
  dht.begin();

  // Configuramos los pines de los LEDs como salidas
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledRojo, OUTPUT);
}

void loop() {
  delay(2000);

  // Leemos la humedad y temperatura desde el sensor
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature(); // Grados Celsius

  // Validamos las lecturas del sensor
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error al leer datos del DHT11.");
    return; // Salir del loop y volver a intentar en el siguiente ciclo
  }

  // Imprimimos los datos por el monitor serial
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print(" %\tTemperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // LED verde encendido si la temperatura es inferior a 28°C
  digitalWrite(ledVerde, (temperatura < 28) ? HIGH : LOW);

  // LED azul encendido si la temperatura es superior a 30°C
  digitalWrite(ledAzul, (temperatura > 30) ? HIGH : LOW);

  // LED rojo encendido si la temperatura está entre 28 y 30 (ambos excluidos)
  // y la humedad es inferior al 70%
  if (temperatura >= 28 && temperatura <= 30 && humedad < 70) {
    digitalWrite(ledRojo, HIGH);
  } else {
    digitalWrite(ledRojo, LOW);
  }
}