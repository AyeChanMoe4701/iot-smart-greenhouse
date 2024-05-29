int tri = 4; //triger pin
int eco = 5; //echopin
int alarm = 8; 
int duration;        //travel time
int distance;        //distance
int ultrasonic_threshold = 6;
int LDR = A0;
int enviroment_light;
int ldr_threshold = 600;
int led = 3; // relay
void setup()
{
   pinMode(tri, OUTPUT);
   pinMode(eco, INPUT);    
   pinMode(alarm, OUTPUT);
   Serial.begin(9600);
   pinMode(LDR, INPUT);
   pinMode(led, OUTPUT); // sets "Relay" to "output"
}
void loop(){
 enviroment_light = analogRead(LDR);
  
 Serial.println(enviroment_light);
  
 if(enviroment_light<=ldr_threshold){
 digitalWrite(led, LOW); 
 }
 else{
 digitalWrite(led, HIGH); 
 }
 
  digitalWrite(tri, HIGH);
  delayMicroseconds(2);
  digitalWrite(tri, HIGH);
  delayMicroseconds(10);
  digitalWrite(tri, LOW);

duration = pulseIn( eco, HIGH);
distance = duration * 0.0343 / 2;
delay(1000);
Serial.println(distance);
   
if(distance>=ultrasonic_threshold){
  digitalWrite(alarm, HIGH);
  }  
else{
  digitalWrite(alarm, LOW);  
  }
}
