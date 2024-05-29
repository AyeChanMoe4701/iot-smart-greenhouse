#include <lcd.h>  //add library files
#include "DHT.h"

#define DHTPIN 13     // the pin connected the DHT sensor
DHT dht(DHTPIN, DHT11);
lcd Lcd;  //define a Lcd class instance 

void setup() {
  Lcd.Init(); //initialize
  Lcd.Clear();  //clear

  dht.begin();
}
char string[10];

//lcd displays humidity and temperature values
void loop() {
  Lcd.Cursor(0,0);
  Lcd.Display("Humidity:"); 
  Lcd.Cursor(0,9);
  float humidity = dht.readHumidity();
  Lcd.DisplayNum(humidity);
  Lcd.Cursor(0,12);
  Lcd.Display("%RH");
  
  Lcd.Cursor(2,0);
  Lcd.Display("Temperature:");
  Lcd.Cursor(2,12);
  float temperature = dht.readTemperature();
  Lcd.DisplayNum(temperature);
  Lcd.Cursor(2,15);
  Lcd.Display("C");
  delay(200);
}
