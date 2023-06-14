int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float readSharp()
{
  float voMeasured = 0;
  float calcVoltage = 0;
  float dustDensity = 0;
  digitalWrite(Digital_sharp,LOW);
  delayMicroseconds(samplingTime); 
  voMeasured = analogRead(Analog_sharp);
  delayMicroseconds(deltaTime);
  digitalWrite(Digital_sharp,HIGH);
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (3.3 / 4095.0);
  dustDensity = 0.17 * calcVoltage - 0.1; 
  return dustDensity;
}

void displaySharp()
{
  float dustDensity = readSharp()*1000;
  char buf[30];
  DisplayString(53,6,"DUST : ");
  Serial.print("Dust : ");
  Serial.println(dustDensity);
  String displayString = "-> " + String((int)dustDensity) + " ug/m3      ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(53,7,buf);
}

void printSharpData()
{
  float dustDensity = readSharp()*1000;
  char buf[30];
  String displayString = "Dust = " + String((int)dustDensity) + " ug/m3       ";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,6,buf);
}
