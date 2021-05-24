#include <ArduinoJson.h>


// VERSION DE ARDUINOJSON.H ES LA 501 5-13-2
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
// ***************************************CONEXION*********************************
const char* ssid = "INFINITUM3F9C_2.4";
const char* password = "Mariana016";
HTTPClient http;
//****************************************VARIABLES DE CONEXION AL SERVIDOR*****************************************

String server = "http://lelebonita.com:9001/banca";
const int sensorPin = 5;
String estado = "";
boolean st = LOW;
String pru;
void setup() {
  Serial.begin(9600);   //iniciar puerto serie
  pinMode(sensorPin , INPUT);  //definir pin como entrada
  WiFiClient client;
    Serial.begin(9600);
    Serial.print("Conectando con ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(2500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");     
  Serial.println(WiFi.localIP());
}
 
void loop(){
  int value = 0;
  value = digitalRead(sensorPin );  //lectura digital de pin
  /*
  if (value == HIGH) {
      Serial.println("Libre");
      estado = "Libre";
      envioDatos();
  }
  else{
    Serial.println("Ocupado");
    estado = "Ocupado";
    envioDatos();
    }*/
  if(value != st){
    if (value == HIGH && st == LOW){
      Serial.println("Libre");
      estado = "Libre";
      envioDatos();
      st = HIGH;
      }       
    }
   if ( value == LOW && st == HIGH){
      if(value == LOW){
        Serial.println("ocupado");
        estado = "Ocupado";
        envioDatos();
        st = LOW;
        }
    }
   
   // st = value;
  delay(5000);
}

void envioDatos(){
  /*
  char json[256];
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["estado"] = estado;
  root.printTo(json, sizeof(json));
  http.addHeader("Content-Type", "application/json");
  Serial.println("\n");
  Serial.println(json);
  http.begin(server);  
  http.POST(json);   
  */
  char json[256];
  /*
  DynamicJsonDocument root(1024);
  root["idbanca"] = 11;
  root["estado"] = estado;
  serializeJson(root,Serial);*/
  WiFiClient client;
  HTTPClient http;
    
  DynamicJsonBuffer jb;
  JsonObject& root = jb.createObject();
  root["idbanca"] = "11";
  root["estado"] = estado;
  root.printTo(json, sizeof(json));
  http.addHeader("Content-Type", "application/json");
  Serial.println("\n");
  Serial.println(json);
  http.begin(client, "http://lelebonita.com:9001/banca");  
  http.POST(json);
  int httpResponseCode = http.POST(json);
  Serial.print(httpResponseCode);
  }
  
