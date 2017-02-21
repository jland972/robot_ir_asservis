
#include <SimpleTimer.h>

SimpleTimer timer;

const int motor1_enablePin = 3; //pwm
int motor1_in1Pin = 11;
int motor1_in2Pin = 12;

int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 9;
int motor2_in2Pin = 8;
int codeuse1=4;
int codeuse2=5;
unsigned int tick_1=0;
unsigned int tick_2=0;
int cmd=0;
const int frequence=50;
float consigne_moteur_nombre_tours_par_seconde=2;
float kp=0.5;


void compteur(){
  tick_1++;
  //tick_2++;  a faire 
 // Serial.println(tick_1);
  }
  
void asservissement(){
  int frequence_codeuse=frequence*tick_1;
  float nb_tour_par_sec=(float)frequence_codeuse/(float)40/(float)48;
  float erreur =consigne_moteur_nombre_tours_par_seconde-nb_tour_par_sec;
 
  tick_1=0;
  cmd=kp*erreur;
  if (cmd<0)cmd=0;
  else if (cmd>255)cmd=255;
  analogWrite(motor1_enablePin,255-cmd);
  //Serial.println(tick_1);
   // DEBUG
    
    Serial.print(nb_tour_par_sec,8);
    Serial.print(" : ");
    Serial.print(erreur,4);
    Serial.println();
    //*/
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
  analogWrite(motor1_enablePin,255);

  // set enablePin high so that motor can turn on:
  
  
delay(5000);
attachInterrupt(codeuse1,compteur,CHANGE);
timer.setInterval(1000/frequence,asservissement);

}


void loop() {
  timer.run();
  delay(10);
}
