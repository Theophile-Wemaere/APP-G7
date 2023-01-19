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
// --------- POTENTIOMETERS----------
#define POT1 PE_2
#define POT2 PE_3

// max 21 char on one line on oled display

void setup() 
{
  InitI2C_Oled();
  InitScreen();
  Display(logo);
  
  Serial.begin(9600);
  Serial.println("Initializing all components");
  
  InitI2C_co2();
  pinMode(POT1,INPUT);
  pinMode(POT2,INPUT);
  //pinMode(Digital_sharp, OUTPUT);
  delay(2000);
  
  Serial.println("Done initializing");
  Display(empty);
}

void loop() 
{
  //mainMenu();
  airMenu();
}

void printAllData()
{
  Serial.println(" --------- NEW DATA ---------");
  printDHT11Data();
  readSensor_co2();
  printSharpData();
}

String menu[4] = {
  "climate quality ",
  "  air quality   ",
  "  hearth rate   ",
  "    options     "
  };

void mainMenu()
{
  DisplayString(0,1," --- HEALTH-EIR ---  ");
  int value = analogRead(POT1);
  Serial.println(value);
  int selectedMenu; 
  String displayString;
  char buf[30];
  
  // pot value 0-4095
  if(value<1000) {selectedMenu = 0;}
  else if(value<2000){selectedMenu = 1;}
  else if(value<3000){selectedMenu = 2;}
  else if(value<4100){selectedMenu = 3;}

  for(int i=0;i<4;i++)
  {
    if(i==selectedMenu)
      displayString = "> " + menu[i] + " < ";
    else
      displayString = "  " + menu[i] + "   ";
    displayString.toCharArray(buf,displayString.length());
    DisplayString(0,i+4,buf);
  }
}

bool displayLogo = true;

void climateMenu()
{
  if(displayLogo)
  {
    Display(climate);
    displayLogo = false;  
  }
  displayDHT11();
  displaySound();
}

void airMenu()
{
  if(displayLogo)
  {
    Display(air);
    displayLogo = false;  
  }
  displayCO2();
  displaySharp();
}

void displaySound()
{
  char buf[30];
  DisplayString(50,6,"SOUND : ");
  String displayString = "-> 59 db     ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(50,7,buf);
}
