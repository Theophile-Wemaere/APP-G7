#include "logo.h"
// ------------- DHT11 --------------
#define DHT11PIN PD_6
// -------------- ECG ---------------
#define ECG PD_1
// -------------- LEDS --------------
#define RED_LED PF_1
#define BLUE_LED PF_2
#define GREEN_LED PF_3
// -------- MICRO-PARTICULES --------
#define Analog_sharp PE_1
#define Digital_sharp PC_4
// -------------- SOUND -------------
#define Micro_in PD_2
// --------- POTENTIOMETERS----------
#define POT1 PE_2
#define POT2 PE_3
// ------------- BUTTON -------------
#define SW1 PF_3
// -------------- SOUND -------------
#define BUZZ PC_7

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
  pinMode(SW1,INPUT_PULLUP);
  pinMode(Digital_sharp, OUTPUT);
  delay(2000);
  
  Serial.println("Done initializing");
  ClearScreen();
}

boolean buttonWasLow = false;
bool displayLogo = true;
int choosedMenu = 0;
/*
 * 0 = main menu
 * 1 = climate quality (temp, humidity, sound)
 * 2 = air quality (CO2,VOC,Dust)
 * 3 = Heart rate
 * 4 = Options
*/
String menu[4] = {
  "climate quality ",
  "  air quality   ",
  "  hearth rate   ",
  "    options     "
  };
int selectedMenu = 0; 

void loop() 
{
  //mainMenu();
  runtime();  
}

void runtime()
{
  boolean buttonValue = digitalRead(SW1);
  
  switch(choosedMenu)
  {
    case 0:
      mainMenu();
      break;
    case 1:
      climateMenu();
      break;
    case 2:
      airMenu();
      break;
    case 3:
      hearthMenu();
      break;
    case 4:
      printAllData();
      break;
  }
      
  if (buttonValue == LOW)  {
      buttonWasLow = true;
  }

  // This if statement will only fire on the rising edge of the button input
  if (buttonValue == HIGH && buttonWasLow)  
  {
    buttonWasLow = false;
    displayLogo = true;

    if(selectedMenu == 1)
    {
      choosedMenu = 1;
      selectedMenu = 0;
    }
    else if(selectedMenu == 2)
    {
      choosedMenu = 2;
      selectedMenu = 0;
    }
    else if(selectedMenu == 3)
    {
      choosedMenu = 3;
      selectedMenu = 0;
    }
    else if(selectedMenu == 4)
    {
      choosedMenu = 4;
      selectedMenu = 0;
    }
    else if(selectedMenu == 0)
    {
      choosedMenu = 0;
      ClearScreen();
    }
  }
}

void printAllData()
{
  Serial.println(" --------- NEW DATA ---------");
  printDHT11Data();
  readSensor_co2();
  printSharpData();
}

void mainMenu()
{
  DisplayString(0,1," --- HEALTH-EIR ---  ");
  int value = analogRead(POT1);
  String displayString;
  char buf[30];
  
  // pot value 0-4095
  if(value<1000) {selectedMenu = 1;}
  else if(value<2000){selectedMenu = 2;}
  else if(value<3000){selectedMenu = 3;}
  else if(value<4100){selectedMenu = 4;}

  for(int i=1;i<=4;i++)
  {
    if(i==selectedMenu)
      displayString = "> " + menu[i-1] + " < ";
    else
      displayString = "  " + menu[i-1] + "   ";
    displayString.toCharArray(buf,displayString.length());
    DisplayString(0,i+3,buf);
  }
}


void hearthMenu()
{
  if(displayLogo)
  {
    Display(hearth);
    displayLogo = false;  
  }
  displayECG();
}

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
