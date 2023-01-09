void setup() 
{
  //Initialize Serial Monitor
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() 
{
  //Write data from HC06 to Serial Monitor
  if(Serial.available())
  {
//    String command = Serial.readString();
//    Serial.println("\nSending command : " + command);
//    Serial1.print(command);
      Serial1.print(Serial.readString());
  }
  if (Serial1.available()) 
  {
    Serial.write(Serial1.read());
  }
}
