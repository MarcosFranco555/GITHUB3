#include <stdint.h>

// Definir pines para los LEDs
uint8_t red_led = 2;   // Pin del LED rojo
uint8_t button = 23;   // Pin del botón

bool led_state = false;

void setup() {
    // Configurar los pines como salida
    Serial.begin(9600);
    pinMode(red_led, OUTPUT);
    pinMode(button, INPUT_PULLUP); // Inicializamos el pin del botón como entrada con pull-up

    digitalWrite(red_led, LOW); // Inicializamos el LED rojo como apagado
}

void loop() {
    if (digitalRead(button) == LOW) { // Si el botón está presionado
        delay(100);  // Pequeño retardo para evitar rebotes
        led_state = !led_state; // Intercambiamos el estado del LED
        digitalWrite(red_led, led_state); // Encender o apagar el LED
    }
}