#define inp PA_7


void setup()
{
  pinMode(inp,INPUT);
  Serial.begin(9600);
}

unsigned long millis1, prev_millis1=0;
int high = 0, value;
boolean new_pick = false;


void loop()
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
