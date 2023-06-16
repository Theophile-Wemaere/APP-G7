unsigned long millis1 = 0, current,duration;
int value;
boolean wasHigh = false;

void readECG()
{
  value = digitalRead(ECG);
  if(value == 1 && !wasHigh)
  {
    wasHigh = true;
    current = millis();
    duration = current - millis1;
    millis1 = current;
    rate = 60000/duration;
    String frame = createFrameCourante(rate);
    Serial1.println(frame);
    if(rate > ecgLimit)
    {
      ecgCounter += 1;
      if(ecgCounter >= 5)
      {
        alarmGoesOff = true;
      }
    }
    else
    {
      ecgCounter = 0;
      alarmGoesOff = false;
    }
  }

  if(value == 0 && wasHigh)
  {
    wasHigh = false;
  }
}

void displayECG()
{
  DisplayString(60,2,"ECG : ");
  char buf[30];
  String displayString = "-> " + String(rate) + " bpm    ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(60,4,buf);
}
