
void readMicro()
{
  float value = analogRead(MICRO)*3.3/4096;
  if(value > 1.5)
    soundQuality = 1;
  else
    soundQuality = 0;
  int R = ((1.65 - value)*255/1.65) / (soundLimit/10);
  if(R < 10)
    R = 10;
  if(R > 255)
    R = 255;
  analogWrite(RED_LED,R);
}
