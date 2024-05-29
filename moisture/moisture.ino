#include <SoftwareSerial.h>
#include <lcd.h>  //add library files
#include "DHT.h"

#define DHTPIN 13     // the pin connected the DHT sensor
DHT dht(DHTPIN, DHT11);
lcd Lcd;  //define a Lcd class instance 

SoftwareSerial nodemcu(2,3);

int aircon = 7;
int N = 9;
int P = 10;
int K = 11;
int water = 12;
int spray = 8;
int moisture_treshold = 840;
int nutrient_treshold1 = 850;
int nutrient_treshold2 = 855;
int nutrient_treshold3 = 860;

void setup() {
  pinMode(N,OUTPUT);
  pinMode(P,OUTPUT);
  pinMode(K,OUTPUT);
  pinMode(water,OUTPUT);
  pinMode(spray,OUTPUT);
  pinMode(aircon,OUTPUT);
  
  Serial.begin(115200);
  nodemcu.begin(115200);
  
  Lcd.Init(); //initialize
  Lcd.Clear();  //clear
  dht.begin();
}

void loop() {

  int moist = analogRead(A0);
  int nutri = analogRead(A1);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  LCD_display(temperature,humidity,moist,nutri);  
  
  // String data = data + moist+","+nutri+","+temperature+","+humidity; // comma will be used a delimeter
  Serial.println(moist); 
  Serial.println(nutri); 
   nodemcu.println(moist);
   nodemcu.println(nutri);
   delay(2000); // 100 milli seconds
  
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
  moist = 0;
  nutri = 0;
}

void LCD_display(float t, float h, int m, int n){
  Lcd.Cursor(0,0);
  Lcd.Display("Humidity:"); 
  Lcd.Cursor(0,9);
  Lcd.DisplayNum(h);
  Lcd.Cursor(0,12);
  Lcd.Display("%RH");
  
  Lcd.Cursor(2,0);
  Lcd.Display("Temperature:");
  Lcd.Cursor(2,12);
  Lcd.DisplayNum(t);
  Lcd.Cursor(2,15);
  Lcd.Display("C");
  delay(3000);
  
  Lcd.Cursor(0,0);
  Lcd.Display("Moisture:"); 
  Lcd.Cursor(0,9);
  Lcd.DisplayNum(m);
  
  Lcd.Cursor(2,0);
  Lcd.Display("Nutrients:");
  Lcd.Cursor(2,10);
  Lcd.DisplayNum(n);
  delay(3000);
  }
