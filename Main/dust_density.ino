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
  Serial.println(voMeasured);
  Serial.println(calcVoltage);
  Serial.println(dustDensity);
  return results;

//  voMeasured *= 1000;
//  calcVoltage *= 1000;
//  dustDensity *= 1000;
//  
//  char payload[30];
//  sprintf(payload,"V%dC%dD%d",int(voMeasured),int(calcVoltage),int(dustDensity));
//  
//  String results(payload);
//  return results;
}
