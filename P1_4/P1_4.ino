#include <stdint.h>

// Definir pines para el LED y los pulsadores
uint8_t ledPin = 2; // Pin del LED
uint8_t p1Pin = 4;   // Pin del pulsador P1
uint8_t p2Pin = 19;   // Pin del pulsador P2

// Variables para temporización
uint64_t startTime = 0;  // Almacena el tiempo de inicio cuando se presiona P1
uint64_t led_interval = 10000; // Tiempo de encendido del LED (10s)
bool ledOn = false;  // Estado del LED

void setup() {
    // Configurar pines como entrada o salida
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(p1Pin, INPUT_PULLUP);
    pinMode(p2Pin, INPUT_PULLUP);
    
    // Inicializar LED apagado
    digitalWrite(ledPin, LOW);
}

void loop() {
    uint64_t actual_millis = millis(); // Obtener el tiempo actual

    // Si se presiona P1, encender el LED y reiniciar el temporizador
    if (digitalRead(p1Pin) == LOW) {
        digitalWrite(ledPin, HIGH);
        startTime = actual_millis;
        ledOn = true;
    }
    
    // Si el LED está encendido, verificar el tiempo transcurrido
    if (ledOn) {
        // Si han pasado 10 segundos, apagar el LED
        if (actual_millis - startTime >= led_interval) {
            digitalWrite(ledPin, LOW);
            ledOn = false;
        }
        
        // Si se presiona P2 antes de que pasen los 10s, apagar el LED
        if (digitalRead(p2Pin) == LOW) {
            digitalWrite(ledPin, LOW);
            ledOn = false;
        }
    }
}
