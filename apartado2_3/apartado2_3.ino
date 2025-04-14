// Definición de pines
const int pirPin = 4;       // Pin del sensor PIR
const int buzzerPin = 23;   // Pin del buzzer

void setup() {
  Serial.begin(115200);

  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Leer el estado del sensor PIR (0 = sin movimiento, 1 = movimiento)
  int movimiento = digitalRead(pirPin);

  // Verificar si se ha detectado movimiento
  if (movimiento == HIGH) {
    // Activar el buzzer
    digitalWrite(buzzerPin, HIGH);
    
    // Imprimir mensaje en el monitor serial
    Serial.println("Se ha detectado movimiento");
  } else {
    // Apagar el buzzer si no hay movimiento
    digitalWrite(buzzerPin, LOW);
    
    Serial.println("No se ha detectado movimiento");
  }

  delay(100);
}