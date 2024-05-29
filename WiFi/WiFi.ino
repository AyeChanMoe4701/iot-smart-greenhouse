#include <lcd.h>
#include <DHT.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SERVER_IP "http://api.thingspeak.com/update?api_key=BC7248Z25H6OCJ19&"
#define WIFI_NAME "AustonMMCampus"
#define WIFI_PW "helloyangon"

int N = 9;
int P = 10;
int K = 11;
int water = 12;
int spray = 8;
int moisture_treshold = 700;
int nutrient_treshold1 = 750;
int nutrient_treshold2 = 760;
int nutrient_treshold3 = 770;
int dhtpin=11;
int sda=A4;
int scl=A5;
DHT dht(dhtpin, 11);
lcd LCD;

void setup(){
  pinMode(N,OUTPUT);
  pinMode(P,OUTPUT);
  pinMode(K,OUTPUT);
  pinMode(water,OUTPUT);
  pinMode(spray,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(WIFI_NAME, WIFI_PW);
  while( WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("CONNECTED");
  

  float temp = 32;
  upload_temp(temp);
}

void loop(){
  //find soil moisture and nutrients
  int moist = analogRead(A0);
  int nutri = analogRead(A1);

  //upload soil moisture and nutrients
  upload_moist(moist);
  upload_nutri(nutri);
  
  Serial.println(moist);
  
  Serial.println(nutri);
  
  digitalWrite(N, LOW);
  digitalWrite(P, LOW);
  digitalWrite(K, LOW);
  digitalWrite(water, LOW);
  digitalWrite(spray, LOW);

 //for water spray
 if(moist >= moisture_treshold){
  digitalWrite(spray, HIGH);
  delay(3000);
  }
 else{
  digitalWrite(spray, LOW); 
  delay(3000); 
  }

 //for nutrient
 if(nutri >= nutrient_treshold3){
  digitalWrite(N, HIGH);
  digitalWrite(P, HIGH);
  digitalWrite(K, HIGH);
  digitalWrite(water, HIGH);
  delay(2000);
  }
 else if(nutri >= nutrient_treshold2){
  digitalWrite(N, HIGH);
  digitalWrite(P, HIGH);
  digitalWrite(K, HIGH);
  digitalWrite(water, HIGH);
  delay(3000);
  }
 else if(nutri >= nutrient_treshold1){
  digitalWrite(N, HIGH);
  digitalWrite(P, HIGH);
  digitalWrite(K, HIGH);
  digitalWrite(water, HIGH);
  delay(4000);
  }
 else{
  digitalWrite(N, LOW);
  digitalWrite(P, LOW);
  digitalWrite(K, LOW);
  digitalWrite(water, LOW);
  delay(1000);
  } 
  //find temp
  
  
  //upload_temp
 
  
}



//////// UTILITIES //////////

void upload_temp(float temp){
  WiFiClient client;
  HTTPClient http;
  String tempStr = String(temp);
  String tempQuery = "field1=";
  String url = SERVER_IP +tempQuery + tempStr;
  Serial.println("sending");
  http.begin(client, url);
  http.GET();
  http.end();
}

void upload_humi(float humi){
  WiFiClient client;
  HTTPClient http;
  String humiStr = String(temp);
  String humiQuery = "field2=";
  String url = SERVER_IP +humiQuery + humiStr;
  Serial.println("sending");
  http.begin(client, url);
  http.GET();
  http.end();
}

void upload_moist(int moist){
  WiFiClient client;
  HTTPClient http;
  String moistStr = String(moist);
  String moistQuery = "field3=";
  String url = SERVER_IP +moistQuery + moistStr;
  Serial.println("sending");
  http.begin(client, url);
  http.GET();
  http.end();
}

void upload_nutri(int nutri){
  WiFiClient client;
  HTTPClient http;
  String nutriStr = String(nutri);
  String nutriQuery = "field4=";
  String url = SERVER_IP +nutriQuery + nutriStr;
  Serial.println("sending");
  http.begin(client, url);
  http.GET();
  http.end();
}
