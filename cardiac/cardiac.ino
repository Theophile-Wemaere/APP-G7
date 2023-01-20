#define inp PD_1
// -------------- SOUND -------------
#define BUZZ PC_7

void setup()
{
  pinMode(inp,INPUT);
  pinMode(BUZZ,OUTPUT);
  Serial.begin(9600);
}

unsigned long millis1 = 0, current, prev_millis1,duration;
int high = 0, value;
boolean new_pick = false, wasHigh = false;

void loop()
{
  Rate();

}
void Rate()
{
  value = digitalRead(inp);
  //Serial.println(value);
  if(value == 1 && !wasHigh)
  {
    wasHigh = true;
    current = millis();
    Serial.println(current);
    duration = current - millis1;
    millis1 = current;
    int rate = 60000/duration;
    Serial.print("Duration :");
    Serial.print(duration);
    Serial.print(" - Rate : ");
    Serial.println(rate);
    digitalWrite(BUZZ,HIGH);
  }

  
  if(value == 0 && wasHigh)
  {
    digitalWrite(BUZZ,LOW);
    wasHigh = false;
  }
}

void LongRate()
{
  value = digitalRead(inp);
  //Serial.println(value);
  millis1 = millis();
  if(millis1 - prev_millis1 >= 10000)
  {
    prev_millis1 = millis1;
    Serial.println("Votre fréquence cardiaque est de " + String(high*6) + "/bpm");
    high = 0;
  }
  else
  {
    if(value && !new_pick)
    {
        high += 1;
        new_pick = true;
    }
     

    if(!value)
      new_pick = false;
  }
}
