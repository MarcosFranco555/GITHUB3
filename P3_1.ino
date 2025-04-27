#include <WiFi.h>
#include "time.h"
#include <stdint.h>

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
struct tm timeinfo;




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

}

void loop() {
  
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "%d %m %Y %H:%M:%S");
  delay(1000);

}
