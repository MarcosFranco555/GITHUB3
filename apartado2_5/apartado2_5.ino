#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === Configuración de la pantalla OLED ===
#define SCREEN_WIDTH 128       // Ancho de la pantalla en píxeles
#define SCREEN_HEIGHT 64       // Alto de la pantalla en píxeles
#define OLED_RESET -1          // No se usa pin de reset físico

// Objeto de la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === Definición del pin del sensor infrarrojo ===
#define IR_SENSOR_PIN 18       // Pin digital conectado al sensor IR

void setup() {
  // Inicia la comunicación serie
  Serial.begin(115200);

  // Configura el pin del sensor como entrada
  pinMode(IR_SENSOR_PIN, INPUT);

  // Inicializa la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se detectó la pantalla OLED");
    while (true); // Detiene la ejecución si la pantalla falla
  }

  // Mensaje de bienvenida al iniciar el sistema
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("IR System");
  display.display();
  delay(2000); // Espera para mostrar el mensaje de inicio
}

void loop() {
  // Lee el valor digital del sensor IR
  int sensorState = digitalRead(IR_SENSOR_PIN);

  // Limpia la pantalla antes de actualizar el contenido
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);

  // Muestra mensaje dependiendo del estado del sensor
  if (sensorState == LOW) {
    display.println("Hay un    obstaculo");
    Serial.println("Se ha detectado un obstáculo.");
  } else {
    display.println("No hay    obstaculo");
    Serial.println("Sin obstáculo.");
  }

  // Actualiza la pantalla con el contenido nuevo
  display.display();
  delay(500); // Pausa breve antes de repetir la lectura
}