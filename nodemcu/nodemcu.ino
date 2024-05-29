#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SERVER_IP "api.thingspeak.com/"
#define WIFI_NAME "AustonMMCampus"
#define WIFI_PW "helloyangon"

float temp;
float humi;
int moist;
int npk;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(WIFI_NAME  , WIFI_PW);
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("Wifi connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() && WiFi.status() == WL_CONNECTED){
    
    String incoming_data = Serial.readString(); 

    char *temp_moisture = strtok(incoming_data, ",");
    char *temp_nutrient = strtok(NULL, ","); 
    char *temp_temperature = strtok(NULL, ",");
    char *temp_humidity = strtok(NULL, ",");

    temp = atof(temp_temperature);
    humi = atof(temp_humidity);
    moist = atoi(temp_moisture);
    npk = atoi(temp_nutrient);

    upload_temp(temp);
    upload_humi(humi);
    upload_moist(moist);
    upload_npk(npk);
  }
}

void upload_moist (int moist){
  WiFiClient client;
  HTTPClient http;

  String moist_url = "http://api.thingspeak.com/update?api_key=LQA3CF8VY35CDIDV&field1=" + moist;
  Serial.println(moist_url);
  
  http.begin(client, moist_url);

 int httpCode = http.GET();
  http.end();
}
  
void upload_npk (int npk){
  WiFiClient client;
  HTTPClient http;

 String nutri_url = "http://api.thingspeak.com/update?api_key=LQA3CF8VY35CDIDV&field2=" + npk;
  Serial.println(nutri_url);
  
  http.begin(client, nutri_url);

 int httpCode = http.GET();
  http.end();
}

void upload_temp (int temp){
  WiFiClient client;
  HTTPClient http;

 String temp_url = "http://api.thingspeak.com/update?api_key=LQA3CF8VY35CDIDV&field3=" + temp;
  Serial.println(temp_url);
  
  http.begin(client, temp_url);

 int httpCode = http.GET();
  http.end();
}

void upload_humi (int humi){
  WiFiClient client;
  HTTPClient http;

 String humi_url = "http://api.thingspeak.com/update?api_key=LQA3CF8VY35CDIDV&field4=" + humi;
  Serial.println(nutri_url);
  
  http.begin(client, humi_url);

 int httpCode = http.GET();
  http.end();
}
