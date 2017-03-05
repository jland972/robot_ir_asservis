
#include <SimpleTimer.h>

SimpleTimer timer;

const int motor1_enablePin = 3; //pwm
int motor1_in1Pin = 11;
int motor1_in2Pin = 12;

const int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 9;
int motor2_in2Pin = 8;
int codeuse1=4;
int codeuse2=5;
unsigned int tick_1=0;
unsigned int tick_2=0;
int cmd1=0;
int cmd2=0;
const int frequence=50;
float consigne=15;
float kp1=150;
float kp2=150;// essayer : 100 ou 300
float ki1=2;
float ki2=2;
float kd1=300;
float kd2=300;
float somme_erreur = 0;
float delta_erreur=0;
float erreur_precedente=0;

int i;
int j;
int val;
int val2;
int redpin=0;
int redpin2=1;
int d;

int distanceFunction(){
   i=analogRead(redpin);
    val=(6762/(i-9))-4; 
  return val;
}

int mouvement(int d){
  if (d<5) 
 {
  digitalWrite(motor1_in1Pin, HIGH);   
  digitalWrite(motor1_in2Pin, LOW);  
  digitalWrite(motor2_in1Pin, HIGH);   
  digitalWrite(motor2_in2Pin, LOW);  
 
 }
 else if (d>5 and d<20)
     {
     digitalWrite(motor1_in1Pin, HIGH);   
     digitalWrite(motor1_in2Pin, LOW);  
     digitalWrite(motor2_in1Pin, LOW);   
     digitalWrite(motor2_in2Pin, HIGH);  
     }
    
     
     else
     {
     digitalWrite(motor1_in1Pin, LOW);   
     digitalWrite(motor1_in2Pin, HIGH);  
     digitalWrite(motor2_in1Pin, LOW);   
     digitalWrite(motor2_in2Pin, HIGH);  
 }
 
  
}

void compteur (){
  tick_1++;
  tick_2++;  
 // Serial.println(tick_1);
  }
  
void asservissement1(){
  
  int frequence_codeuse=frequence*tick_1;
  float nb_tour_par_sec=frequence_codeuse/20;
  float erreur =consigne-nb_tour_par_sec;
  float delta_erreur = erreur-erreur_precedente;
  erreur_precedente = erreur;
  somme_erreur += erreur;
 
  
  cmd1=kp1*erreur+ki1*somme_erreur+kd1*delta_erreur;
  if (cmd1<0)cmd1=0;
  else if (cmd1>255)cmd1=255;
  analogWrite(motor1_enablePin,cmd1);
  //Serial.println(tick_1);
   // DEBUG
    
    Serial.print(nb_tour_par_sec,8);
   //Serial.print(" : ");
   // Serial.print(erreur,4);
   Serial.println();
    //*/
    tick_1=0;
}
void asservissement2(){
  
  int frequence_codeuse=frequence*tick_2;
  float nb_tour_par_sec=frequence_codeuse/20;
  float erreur =consigne-nb_tour_par_sec;
  float delta_erreur = erreur-erreur_precedente;
  erreur_precedente = erreur;
  somme_erreur += erreur;
  
  cmd2=kp2*erreur+ki2*somme_erreur+kd2*delta_erreur;
  if (cmd2<0)cmd2=0;
  else if (cmd2>255)cmd2=255;
  analogWrite(motor2_enablePin,cmd2);
  //Serial.println(tick_2);
   // DEBUG
    
    Serial.print(nb_tour_par_sec,8);
   // Serial.print(" : ");
   // Serial.print(erreur,4);
    Serial.println();
    //*/
    tick_2=0;
    }

void setup() {
  Serial.begin(115200);
  // set all the other pins you're using as outputs:
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor1_enablePin, OUTPUT);
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
 
   digitalWrite(motor1_in1Pin, HIGH);   
  digitalWrite(motor1_in2Pin, LOW);  
  digitalWrite(motor2_in1Pin, HIGH);   
  digitalWrite(motor2_in2Pin, LOW);  
  analogWrite(motor1_enablePin,0);
  analogWrite(motor2_enablePin,0);
  // set enablePin high so that motor can turn on:
  
  
delay(5000);
attachInterrupt(codeuse1,compteur,RISING);
timer.setInterval(1000/frequence,asservissement1);
timer.setInterval(1000/frequence,asservissement2);
}


void loop() {
  timer.run();
  // d=distanceFunction();
   // mouvement(d);
 
  delay(10);
}
