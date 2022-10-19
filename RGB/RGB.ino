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
  //blinkYellow();
  rainbowColors();
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

void blinkYellow()
{
  digitalWrite(R,HIGH);
  digitalWrite(G,HIGH);
  digitalWrite(B,LOW);
  delay(500);
  digitalWrite(R,LOW);
  digitalWrite(G,LOW);
  delay(500);
}

void rainbowColors()
{
  rgbColor(255,0,0); // red
  delay(500);
  rgbColor(0,255,0); // green 
  delay(500);
  rgbColor(0,0,255); // blue 
  delay(500);
  rgbColor(255,255,0); // yellow
  delay(500);
  rgbColor(255,0,255); // rose 
  delay(500);
  rgbColor(0,255,255); // cyan 
  delay(500);
  rgbColor(255,255,255); // white
  delay(500);
}

void rgbColor(int Red, int Green, int Blue)
{
  analogWrite(R,Red);
  analogWrite(G,Green);
  anallogWrite(B,Blue);
}

