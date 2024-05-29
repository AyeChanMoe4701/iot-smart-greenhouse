int LDR = A0;
int LED1 = 8;
int LED2 = 7;
int LED3 = 6;
int readValue;
int threshold = 800;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readValue = analogRead(LDR);
  
  Serial.println(readValue);
  
   if(readValue<=threshold){
 digitalWrite(LED,LOW);
 
 }
 else{
 digitalWrite(LED,HIGH);
 
 }
 delay(1000);
}
