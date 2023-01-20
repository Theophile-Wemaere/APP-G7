unsigned long millis1 = 0, current,duration;
int value;
boolean  wasHigh = false;

void displayECG()
{
  value = digitalRead(ECG);
  if(value == 1 && !wasHigh)
  {
    wasHigh = true;
    current = millis();
    Serial.println(current);
    duration = current - millis1;
    millis1 = current;
    int rate = 60000/duration;
    DisplayString(70,2,"ECG : ");

    char buf[30];
    String displayString = "-> " + String(rate) + " ug/m3      ";
    displayString.toCharArray(buf,displayString.length());
    DisplayString(70,4,buf);
  }

  
  if(value == 0 && wasHigh)
  {
    wasHigh = false;
  }
}
