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
// -------------- BUZZER ------------
#define BUZZ PC_7
// -------------- MICRO -------------
#define MICRO PD_3

// max 21 char on one line on oled display

void setup() 
{
  InitI2C_Oled();
  InitScreen();
  Display(logo);
  
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.setTimeout(10);
  //Serial.println("Initializing all components");
  
  InitI2C_co2();
  pinMode(POT1,INPUT);
  pinMode(POT2,INPUT);
  pinMode(ECG,INPUT);
  pinMode(SW1,INPUT_PULLUP);
  pinMode(Digital_sharp, OUTPUT);
  pinMode(BUZZ,OUTPUT);
  pinMode(MICRO,INPUT);
  pinMode(RED_LED,OUTPUT);
  delay(2000);
  //Serial.println("Done initializing");
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

/*String code_sensor[6] = {
  "701",
  "",
}*/

int selectedMenu = 0;
int ecgLimit = 100;
int soundLimit = 10;
int rate;
int ecgCounter = 0;
int soundQuality = 0;

unsigned long millis2,prev_millis2 = 0;
unsigned long millis3,prev_millis3 = 0;

boolean alarmGoesOff = false;
boolean buzz_state = true;

void loop() 
{
  readECG();
  readMicro();

  millis3 = millis();
  if(millis3 - prev_millis3 >= 1000)
  {
    prev_millis3 = millis3;
    String frame = createFrame(rate);
    Serial1.println(frame);
  }
  
  if(alarmGoesOff)
  {
    millis2 = millis();
    if(millis2 - prev_millis2 >= 500)
    {
      prev_millis2 = millis2;
      buzz_state = !buzz_state;
      digitalWrite(BUZZ,buzz_state);
    }
  }
  else
  {
    digitalWrite(BUZZ,LOW);
  }
  runtime();  
  if(Serial1.available()) 
  {
    Serial.print(rate);
    Serial.print("  - Response : ");
    Serial.println(Serial1.read());  
  }
}

String createFrame(int value)
{
                              // courante  n°equipe  ecriture 
  String courante = "1007E1"; // 1         007E      1
  int minutes = millis() / 60000 ; 
  int secondes = millis() % 60000 / 1000;
  
  char hexValue[3]; // 2 characters for the hexadecimal representation and 1 for the null terminator
  char hexMinutes[2];
  char hexSecondes[2];

  sprintf(hexMinutes, "%X", minutes);
  sprintf(hexSecondes, "%X", secondes);
  sprintf(hexValue, "%X", value);
  
  // Ensure the output is exactly 2 characters long
  if (strlen(hexValue) == 1) {
    memmove(hexValue + 1, hexValue, strlen(hexValue) + 1);
    hexValue[0] = '0';
  }
  Serial.println(millis());
  Serial.println(String(minutes) + " : " + String(secondes));
  Serial.println(courante +" 701 " + String(hexValue) + " " + String(hexMinutes) + " " + String(hexSecondes) + " 00");
  String frame = courante + "701" + String(hexValue) + String(hexMinutes) + String(hexSecondes) + "00";
  Serial.println(frame);
  return frame;
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
      optionMenu();
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
      ClearScreen();
      selectedMenu = 0;
    }
    else if(selectedMenu == 2)
    {
      choosedMenu = 2;
      ClearScreen();
      selectedMenu = 0;
    }
    else if(selectedMenu == 3)
    {
      choosedMenu = 3;
      ClearScreen();
      selectedMenu = 0;
    }
    else if(selectedMenu == 4)
    {
      choosedMenu = 4;
      ClearScreen();
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
  Serial.println("  --------- NEW DATA ---------");
  printDHT11Data();
  readSensor_co2();
  printSharpData();
}

void mainMenu()
{
  DisplayString(0,1," --- TAKE-EIR ---  ");
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

void airMenu()
{
  if(displayLogo)
  {
    DisplayFrom(air,85);
    displayLogo = false;  
  }
  displayCO2();
  displaySharp();
}

void climateMenu()
{
  if(displayLogo)
  {
    DisplayFrom(climate,85);
    displayLogo = false;
  }
  displayDHT11();
  displaySound();
}

void hearthMenu()
{
  if(displayLogo)
  {
    DisplayFrom(hearth,80);
    displayLogo = false;
  }
  displayECG();
  
}

void optionMenu()
{
  String displayString;
  char buf[30];
  if(displayLogo)
  {
    DisplayFrom(gear,75);
    displayLogo = false;  
  }
  
  int value = analogRead(POT1);
  
  DisplayString(60,0,"ECG ALARME : ");
  if(value < 2040)
  {
    int value2 = analogRead(POT2);
    ecgLimit = 50 + (value2 * 100)/4096;
    displayString = "> " + String(ecgLimit) + " bpm    ";
  }
  else
    displayString = "  " + String(ecgLimit) + " bpm    ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(60,2,buf);

  DisplayString(60,4,"SOUND LED : ");
  if(value > 2050)
  {
    int value2 = analogRead(POT2);
    soundLimit = (value2 * 100)/4096;
    displayString = "> " + String(soundLimit) + " %    ";
  }
  else
    displayString = "  " + String(soundLimit) + " %    ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(60,6,buf);
}

void displaySound()
{
  char buf[30];
  DisplayString(50,6,"SOUND : ");
  String quality;
  if(soundQuality == 0)
    quality = "calm        ";
  else if(soundQuality == 1)
    quality = "chatting       ";;
    
  String displayString = "-> " + quality;
  displayString.toCharArray(buf,displayString.length());
  DisplayString(50,7,buf);
}
