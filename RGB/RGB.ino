#define R A7
#define G A6
#define B A5

void setup() 
{
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  digitalWrite(R,LOW);
  digitalWrite(G,LOW);
  digitalWrite(B,LOW);
}

void loop() {
  // put your main code here, to run repeatedly: 
  //blink();
}

void blink()
{
  digitalWrite(R,HIGH);
  delay(3000);
  digitalWrite(R,LOW);
  digitalWrite(G,HIGH);
  delay(3000);
  digitalWrite(G,LOW);
  digitalWrite(B,HIGH);
  delay(3000);
  digitalWrite(B,LOW);
  digitalWrite(R,HIGH);
  digitalWrite(G,HIGH);
  delay(3000);
  digitalWrite(R,LOW);
  digitalWrite(G,LOW);
}
