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



#define measurePin PE_1 //Connect dust sensor to Tiva Analogic pin
#define ledPower PC_4   //Connect the led driver pin of dust sensor to Tiva Digital pin

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
}

void loop(){
  digitalWrite(ledPower,LOW); // Allumage de la ILED (logique inverse à cause du transitor pnp)
  delayMicroseconds(samplingTime); // on attend que la mesure soit stable

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // extinction de la ILED
  delayMicroseconds(sleepTime);

  // 0 - 3.3V converti en 0 - 4095 valeurs numeriques (12 bits)
  // tension de sortie du capteur
  calcVoltage = voMeasured * (3.3 / 4095.0);

  // equation lineaire issue de la regression lineaire realisee
  dustDensity = 0.17 * calcVoltage - 0.1;

  Serial.print("Raw Signal Value (0-4095): ");
  Serial.print(voMeasured);

  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);

  Serial.print(" - Dust Density: ");
  Serial.println(dustDensity); // unite : mg/m3

  delay(1000);
}
