int tri = 2; //triger pin
int eco = 3; //echopin
int alarm = 8; //relay
int duration;        //travel time
int distance;        //distance
int hightreshold = 4;
void setup() {
  // put your setup code here, to run once:
    pinMode(tri, OUTPUT);
    pinMode(eco, INPUT);
    
    pinMode(alarm, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
     digitalWrite(tri, HIGH);
  delayMicroseconds(2);
 digitalWrite(tri, HIGH);
delayMicroseconds(10);
digitalWrite(tri, LOW);

duration = pulseIn( eco, HIGH);
distance = duration * 0.0343 / 2;
delay(1000);
Serial.println(distance);
  
 
if(distance>=hightreshold){
  digitalWrite(alarm, HIGH);
  }
  
 else{
  digitalWrite(alarm, LOW);  
  }

}
