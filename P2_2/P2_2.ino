#include <stdint.h>

// Pines del LED RGB
#define pinLed1 18   // Rojo
#define pinLed2 19   // Verde
#define pinLed3 23   // Azul

// Pin del fotoresistor (LDR)
#define pinLDR 4

// Umbrales de luz 
const int umbralBajo = 1000;  
const int umbralAlto = 3000;  

int luz = 0; // Valor leído del fotoresistor

void setup() {
    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);
    pinMode(pinLed3, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    // Leer la intensidad de luz
    luz = analogRead(pinLDR);
    Serial.println(luz);

    // Control del LED RGB según el nivel de luz
    if (luz < umbralBajo) {
        // Muy poca luz 
        digitalWrite(pinLed1, HIGH);  // Rojo
        digitalWrite(pinLed2, LOW);
        digitalWrite(pinLed3, LOW);
    } else if (luz < umbralAlto) {
        // Luz media - (verde)
        digitalWrite(pinLed1, LOW);
        digitalWrite(pinLed2, HIGH);
        digitalWrite(pinLed3, LOW);
    } else {
        // Suficiente luz - apagar LED
        digitalWrite(pinLed1, LOW);
        digitalWrite(pinLed2, LOW);
        digitalWrite(pinLed3, LOW);
    }

    delay(100); // Pequeña pausa
}