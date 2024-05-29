#include <SoftwareSerial.h>
// #include <lcd.h>  //add library files
#include "DHT.h"
#include <Servo.h>

Servo myservo1;
Servo myservo2;

#define DHTPIN 11     // the pin connected the DHT sensor
DHT dht(DHTPIN, DHT11);
// lcd Lcd;  //define a Lcd class instance 

SoftwareSerial nodemcu(2,3);

int aircon = 7;//relay error
int N = 9; //relar error
int P = 10; //relay error
int K = 13;
int water = 12;
int spray = 8;
float temperature_threshold = 40;
int moisture_threshold = 500;
int nutrient_threshold1 = 1000;
int nutrient_threshold2 = 1020;
int nutrient_threshold3 = 1030;
void setup() {
  pinMode(N,OUTPUT);
  pinMode(P,OUTPUT);
  pinMode(K,OUTPUT);
  pinMode(water,OUTPUT);
  pinMode(spray,OUTPUT);
  pinMode(aircon,OUTPUT);
  myservo1.attach(4);
  myservo2.attach(5);
  
  Serial.begin(115200);
  nodemcu.begin(115200);
  
 // Lcd.Init(); //initialize
 // Lcd.Clear();  //clear
  dht.begin();
}
 char string[10];

void loop() {
  digitalWrite(N, HIGH);
  digitalWrite(P, HIGH);
  digitalWrite(K, HIGH);
  digitalWrite(water, HIGH);
  digitalWrite(spray, LOW);
  digitalWrite(aircon, HIGH);

  int moist = analogRead(A0);
  int nutri = analogRead(A1);
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();

   String data = data + moist+","+nutri+","+temperature+","+humidity; // comma will be used a delimeter
   Serial.println(data); 
   nodemcu.println(data);

 if(temperature >= temperature_threshold){
    digitalWrite(aircon, LOW);
    myservo1.write(0);// set the rotation angle of the motor
    delay(500);
    myservo1.write(60);// set the rotation angle of the motor
    delay(10);
    myservo2.write(60);// set the rotation angle of the motor
    delay(500);
    myservo2.write(0);// set the rotation angle of the motor
    delay(10);
    }
   else{
    digitalWrite(aircon, HIGH);
    }

 //for water spray
 if(moist >= moisture_threshold){
  digitalWrite(spray, HIGH);
  delay(3000);
  }
 else{
  digitalWrite(spray, LOW); 
  delay(3000); 
  }

 //for nutrient
 if(nutri >= nutrient_threshold3){
  digitalWrite(N, LOW);
  digitalWrite(P, LOW);
  digitalWrite(K, LOW);
  digitalWrite(water, LOW);
  delay(2000);
  }
 else if(nutri >= nutrient_threshold2){
  digitalWrite(N, LOW);
  digitalWrite(P, LOW);
  digitalWrite(K, LOW);
  digitalWrite(water, LOW);
  delay(3000);
  }
 else if(nutri >= nutrient_threshold1){
  digitalWrite(N, LOW);
  digitalWrite(P, LOW);
  digitalWrite(K, LOW);
  digitalWrite(water, LOW);
  delay(4000);
  }
 else{
  digitalWrite(N, HIGH);
  digitalWrite(P, HIGH);
  digitalWrite(K, HIGH);
  digitalWrite(water, HIGH);
  delay(1000);
  } 

  data = "";
}

/*void LCD_display(int t, int h, int m, int n){
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
  }*/
