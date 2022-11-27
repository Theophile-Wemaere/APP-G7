// ---------------- DEBUT EN TETE --------------------------------------//
// NOM :             CO2_TIVA_PWM                                       //
//                                                                      //
// AUTEURS : Groupe G7E                                                 //
//                                                                      //
// VERSION :    1.3         G7E              novembre 2022              // 
//   Récupération du taux de CO2 et de particule organique dans l'air   //
// HISTORIQUE : Aucun                                                   //
//                                                                      //
// ENTREES :                                                            //
//  PWM_PIN : port PWM sur A3 (PE_0)                                    //
//                                                                      //                                                                 
// SORTIES :                                                            //
//  VOC (ppb) et CO2 (ppm) (type String), respectivement les taux de    //
//  particules organique et de CO2 dans l'air                           //
//                                                                      //                                              
// MODIFIEES :                                                          //
//                                                                      //
// LOCALES :                                                            //
//                                                                      //
//                                                                      //
// FONCTIONS APPELEES : PulseIn()                                       //                                    
//                                                                      //
//                                                                      //
// ALGO - REFERENCES :                                                  //
//                                                                      //
// ---------------- FIN EN TETE ----------------------------------------//

#define PWM_PIN A3

int pwm_value;

void setup() 
{
  pinMode(PWM_PIN, INPUT);
  Serial.begin(115200);
}
 
bool test = false;
float voc, co2;

void loop()
{
  pwm_value = pulseIn(PWM_PIN,HIGH);
  float percent = (pwm_value/1000)*100/33.3;
  if(test) // you either receive the CO2 value or the VOC value so you need to switch each time
  {
    co2 = 40*percent-1800;
  }
  else
  {
    voc = 25*percent-125;
  }
  Serial.print(co2);
  Serial.print(" ");
  Serial.println(voc);
  test = !test;
}
