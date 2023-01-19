#include <dht11.h>

dht11 DHT11;

float * readDHT11()
{
  int chk = DHT11.read(DHT11PIN);
  float humidity = (float)DHT11.humidity;
  float temperature = (float)DHT11.temperature;

  
  static float results[2];
  results[0] = humidity;
  results[1] = temperature;
  return results;
}

void printDHT11Data()
{
  char buf[30];
  
  float * resultsDHT11 = readDHT11();
  float humidity = resultsDHT11[0];
  float temperature = resultsDHT11[1];
  
  String displayString = "Temperature = " + String((int)temperature) + " C      ";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,1,buf);
  
  displayString = "Humidity = " + String((int)humidity) + " %      ";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,2,buf);
}

void displayDHT11()
{
  char buf[30];
  
  float * resultsDHT11 = readDHT11();
  float humidity = resultsDHT11[0];
  float temperature = resultsDHT11[1];

  DisplayString(50,0,"TEMPERATURE : ");
  String displayString = "-> " + String((int)temperature) + " C      ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(50,1,buf);
  
  DisplayString(50,3,"HUMIDITY : ");
  displayString = "-> " + String((int)humidity) + " %      ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(50,4,buf);
}
