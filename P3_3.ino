#include <WiFi.h>
#include "time.h"
#include <stdint.h>

#include <PubSubClient.h>

//WIFI
const char* ssid     = "ALUMNOS_CICLOS";
const char* pasword  = "Ciclos2025sz?";

//servidor para fecha y hora
const char* ntpServer = "es.pool.ntp.org";
//zona horaria
const int32_t gmtOffset_sec = 3600;
//horario de verano
const int32_t daylightOffset_sec = 0;

//Estructura para trabajar con ntp
struct tm timeinfo ;

//MQTT
const char* mqtt_username = "marcos";
const char* mqtt_password = "1234";
const char* server = "broker.emqx.io";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

//Callback para recivir mensajes MQTT
void callback(char* topic, byte* payload, unsigned int lenght){
    Serial.print("Mensaje recibido en el topico: ");
    Serial.println(topic);

    String message;
    for (unsigned int i = 0; i < lenght; i++) {
        message += (char)payload[i];
    }

    Serial.print("Mensaje: ");
    Serial.println(message);

    if(message == "1") {
      Serial.println("ON");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (message == "0") {
      Serial.println("OFF");
      digitalWrite(LED_BUILTIN, LOW);
    }
}

//Funcion para conectar a MQTT
void reconnect () {
  while (!mqtt_client.connected()) {
        Serial.print("Conectando a MQTT...");
        String client_id = "esp32-client-" + String(Wifi.macAddress());
        if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Conectado");
          mqtt_client.subscribe("sensor/boton");
        }
        else {
          Serial.print("Error, codigo: ");
          Serial.println(mqtt_client.state());
          delay(5000);
        }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
   //Conexion Wifi
   Serial.println("Conectando a Wifi...");
   WiFi.begin(ssid, pasword);
   while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
   }
  Serial.println("\nConexion Wifi establecida.");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

  //fecha y hora
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Configurar MQTT
    mqtt_client.setServer(mqtt_server, mqtt_port);
    mqtt_client.setCallback(callback);

}

void loop() {
  
  if (!mqtt_client.connected()) {
      reconnect();
  }
  mqtt_client.loop();//Para procesar mensajes MQTT
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "%d %m %Y %H:%M:%S");
  String currentTime = String(timeinfo.tm_mday) + "/" + String(timeinfo.tm_mon + 1) + "/" + String(timeinfo.tm_year + 1900); 
      if (mqtt_client.connected()) {
        mqtt_client.publish("sensor/hora", "Mensaje");
    }
  delay(1000);

}
