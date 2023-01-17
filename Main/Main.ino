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
  InitI2C_oled();
  InitI2C_co2();
  InitScreen();

  pinMode(Digital_sharp, OUTPUT);
  
  Display(logo);
  delay(2000);
  Serial.println("Done initializing");
}

int CO2, VOC;
float temperature, humidity, voMeasured = 0, calcVoltage = 0, dustDensity = 0;

void loop() 
{
  float* resultsDHT11 = readDHT11();
  delay(100);
  Serial.println("1");
  int* resultsCO2 = readCO2();
  delay(100);
  Serial.println("2");
  float* resultsSharp = readSharp();
  delay(100);
  Serial.println("3");
  humidity = resultsDHT11[0];
  temperature = resultsDHT11[1];

  CO2 = resultsCO2[0];
  VOC = resultsCO2[1];

  voMeasured = resultsSharp[0];
  calcVoltage = resultsSharp[1];
  dustDensity = resultsSharp[2];

  String displayString;

  char buf[30];
  displayString = "Temperature = " + String(temperature,2) + " °C";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,1,buf);
  
  displayString = "Humidity = " + String(humidity, 2) + " %";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,2,buf);
  
  displayString = "CO2 = " + String(CO2) + " ppb";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,3,buf);
  
  displayString = "VOC = " + String(VOC) + " ppm";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,4,buf);
  
  displayString = "Raw Signal Value = " + String(voMeasured);
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,5,buf);
  
  displayString = "Voltage = " + String(calcVoltage);
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,6,buf);
  
  displayString = "Dust Density = " + String(dustDensity) + " mg/m3";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,7,buf);

  delay(1000);
  
}
