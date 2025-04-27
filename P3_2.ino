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

void setup() {
  Serial.begin(115200);

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
    mqtt_client.setServer(server, mqtt_port);

}

void loop() {
  
  mqtt_client.loop();//Para procesar mensajes MQTT
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "%d %m %Y %H:%M:%S");
  String currentTime = String(timeinfo.tm_mday) + "/" + String(timeinfo.tm_mon + 1) + "/" + String(timeinfo.tm_year + 1900); 
      if (mqtt_client.connected()) {
        mqtt_client.publish("sensor/hora", "Mensaje");
    }
  delay(1000);

}
