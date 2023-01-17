// ---------------- DEBUT EN TETE --------------------------------------//
// NOM :                  main                                          //
//                                                                      //
// AUTEURS : Groupe G7E                                                 //
//                                                                      //
// VERSION :    2.4         G7E              novembre 2022              // 
//   Récupération du taux de CO2 et de particule organique dans l'air   //
// HISTORIQUE : Aucun                                                   //
//                                                                      //
// ENTREES :                                                            //
//  Laison I2C : SDA (PB_3, signal data) et SDL (PB_2, signal horloge)  //
//                                                                      //                                                                 
// SORTIES :                                                            //
///  VOC (ppb) et CO2 (ppm) (type String), respectivement les taux de    //
//  particules organique et de CO2 dans l'air                           //
//                                                                      //                                              
// MODIFIEES :                                                          //
//                                                                      //
// LOCALES :                                                            //
//                                                                      //
//                                                                      //
// FONCTIONS APPELEES : InitI2C(), readSensor()                         //                                    
//                                                                      //
//                                                                      //
// ALGO - REFERENCES :                                                  //
//                                                                      //
// ---------------- FIN EN TETE ----------------------------------------//

void setup()
{
  Serial.begin(9600);
  InitI2C();
}

int data[2];

void loop()
{
  //Serial.print("\n\n--- NEW DATA ---\n\n");
  readSensor();
}
