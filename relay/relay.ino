int TPin = 10; //triger pin
int EPin = 9; //echopin
int relay = 8; //relay
int t;        //travel time
int d;        //distance
int hightreshold = 5;
void setup() {
  // put your setup code here, to run once:
    pinMode(TPin, OUTPUT);
    pinMode(EPin, INPUT);
    pinMode(relay, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(TPin, HIGH);
  delayMicroseconds(2);

  //Set the triger pin active for 10 microseconds
  digitalWrite(TPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TPin, LOW);

  //Read the traval time of sound wave from echo pin in microseonds
  t = pulseIn(EPin, HIGH);
  
  //Calculate the distance
  d = t * 0.0343 / 2;
  Serial.println(d);

 if(d<=hightreshold){
  digitalWrite(relay, LOW);
  }
 else{
  digitalWrite(relay, HIGH);  
  }

}
