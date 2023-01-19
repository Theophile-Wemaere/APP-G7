// ---------------- DEBUT EN TETE --------------------------------------//
// NOM :             dust_density                                       //
//                                                                      //
// AUTEURS : Groupe G7E                                                 //
//                                                                      //
// VERSION :    1.2         G7E              octobre 2022               // 
//                  Affichage du taux de microparticules de l’air       //
// HISTORIQUE : Aucun                                                   //
//                                                                      //
// ENTREES :                                                            //
//  voMeasured  entier         Valeur numérique issue du                //
// codage de la tension de sortie du capteur de microparticules         //                                                                                    
// SORTIES :                                                            //
//  calcVoltage           tension de sortie du capteur en Volts         //                                          
//  dustDensity           densite de microparitules de l’air(mg/m3)     //                                                   
// MODIFIEES :                                                          //
//                                                                      //
// LOCALES :                                                            //
//                                                                      //
//                                                                      //
// FONCTIONS APPELEES : analogRead(), pinMode(), delayMicroseconds()    //
//                                                                      //
//                                                                      //
// ALGO - REFERENCES :                                                  //
//                                                                      //
// ---------------- FIN EN TETE ----------------------------------------//

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float * readSharp()
{
  float voMeasured = 0;
  float calcVoltage = 0;
  float dustDensity = 0;
  digitalWrite(Digital_sharp,LOW); // Allumage de la ILED (logique inverse à cause du transitor pnp)
  delayMicroseconds(samplingTime); // on attend que la mesure soit stable

  voMeasured = analogRead(Analog_sharp); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(Digital_sharp,HIGH); // extinction de la ILED
  delayMicroseconds(sleepTime);

  // 0 - 3.3V converti en 0 - 4095 valeurs numeriques (12 bits)
  // tension de sortie du capteur
  calcVoltage = voMeasured * (3.3 / 4095.0);

  // equation lineaire issue de la regression lineaire realisee
  dustDensity = 0.17 * calcVoltage - 0.1;

  static float results[3] = {voMeasured,dustDensity,calcVoltage};
  return results;
}

void displaySharp()
{
  /* 
  * all data are retrieved, but we only print the dust density,
  * because that's the only value interesting in health field 
  */
  float * resultsSharp = readSharp();

  float voMeasured = resultsSharp[0];
  float calcVoltage = resultsSharp[1]; 
  float dustDensity = resultsSharp[3];
  
  char buf[30];

  DisplayString(53,6,"DUST : ");
  String displayString = "-> " + String((int)dustDensity) + " mg/m3      ";
  displayString.toCharArray(buf,displayString.length());
  DisplayString(53,7,buf);
}

void printSharpData()
{
  /* 
  * all data are retrieved, but we only print the dust density,
  * because that's the only value interesting in health field 
  */
  float * resultsSharp = readSharp();

  float voMeasured = resultsSharp[0];
  float calcVoltage = resultsSharp[1]; 
  float dustDensity = resultsSharp[3];
  
  char buf[30];
  String displayString = "Dust = " + String((int)dustDensity) + " mg/m3       ";
  Serial.println(displayString);
  displayString.toCharArray(buf,displayString.length());
  DisplayString(0,6,buf);
}
