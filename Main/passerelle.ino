String equipe = "007E";
String ecriture = "1";

String createFrameCourante(int value)
{
                              
  String courante = "1"; 
  int minutes = millis() / 60000 ; 
  int secondes = millis() % 60000 / 1000;
  
  char hexValue[5]; // 2 characters for the hexadecimal representation and 1 for the null terminator
  char hexMinutes[3];
  char hexSecondes[3];

  sprintf(hexMinutes, "%02X", minutes);
  sprintf(hexSecondes, "%02X", secondes);
  sprintf(hexValue, "%04X", value);
  
  Serial.println(courante + " " + equipe + " " + ecriture + " 7 01 " + String(hexValue) + " " + String(hexMinutes) + " " + String(hexSecondes) + " 00");
  String frame = courante + equipe + ecriture +  "701" + String(hexValue) + String(hexMinutes) + String(hexSecondes) + "3D";
  return frame;
}
