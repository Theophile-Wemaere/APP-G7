#include "logo.h"
// ------------- DHT11 --------------
#define DHT11PIN PD_6
// -------------- LEDS --------------
#define RED_LED PF_1
#define BLUE_LED PF_2
#define GREEN_LED PF_3
// -------- MICRO-PARTICULES --------
#define Analog_sharp PE_1
#define Digital_sharp PB_3
// -------------- SOUND -------------
#define Micro_in PD_2

void setup() 
{
  Serial.begin(9600);
  Serial.println("Initializing all components");
  InitI2C_Oled();
  InitI2C_CO2();
  InitScreen();

  pinMode(Digital_sharp, OUTPUT);
  
  Display(logo);
  delay(2000);
  Serial.println("Done initializing");
  Display(empty);
}

int CO2, VOC;
int i1,i2,i3; // index for string 
float temperature, humidity;
//float voMeasured, calcVoltage, dustDensity;

void loop() 
{
  Serial.println(" --------- NEW DATA ---------");
  float * resultsDHT11 = readDHT11();
  delay(100);
//  int * resultsCO2 = readCO2();
  readCO2();
  delay(100);
  printSharpData();
  delay(100);
  
  humidity = resultsDHT11[0];
  temperature = resultsDHT11[1];

//  CO2 = resultsCO2[0];
//  VOC = resultsCO2[1];

char buf[30];
  String displayString;

  displayString = "Temperature = " + String((int)temperature) + " °C";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,1,buf);
  
  displayString = "Humidity = " + String((int)humidity) + " %";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,2,buf);
  
//  displayString = "CO2 = " + String(CO2) + " ppb";
//  Serial.println(displayString);
//  displayString.toCharArray(buf,displayString.length());
//  DisplayString(0,3,buf);
//  
//  displayString = "VOC = " + String(VOC) + " ppm";
//  Serial.println(displayString);
//  displayString.toCharArray(buf,displayString.length());
//  DisplayString(0,4,buf);
  


  delay(1000);
  
}

void printSharpData()
{
  /* 
  * all data are retrieved, but we only print the dust density,
  * because that's the only value interesting in health field 
  */
  float * resultsSharp = readSharp();
//  String resultsSharp = readSharp();
//  
//  int V = resultsSharp.indexOf("V");
//  int C = resultsSharp.indexOf("C");
//  int D = resultsSharp.indexOf("D");
//
//  float voMeasured = resultsSharp.substring(V+1,C).toInt()/1000.0;
//  float calcVoltage = resultsSharp.substring(C+1,D).toInt()/1000.0; 
//  float dustDensity = resultsSharp.substring(D+1).toInt()/1000.0;
  float voMeasured = resultsSharp[0];
  float calcVoltage = resultsSharp[1]; 
  float dustDensity = resultsSharp[3];
  Serial.println("-_-_-_-_-_-_-_-_-");
  Serial.println(voMeasured);
  Serial.println(calcVoltage);
  Serial.println(dustDensity);

  char buf[30];
  String displayString = "Dust = " + String((int)dustDensity) + " ug/m3 ";
  Serial.println(displayString.length());
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,6,buf);
}
