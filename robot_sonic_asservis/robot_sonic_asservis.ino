
#include <SimpleTimer.h>

SimpleTimer timer;

int motor1_enablePin = 3; //pwm
int motor1_in1Pin = 11;
int motor1_in2Pin = 12;

int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 9;
int motor2_in2Pin = 8;
int codeuse1=5;
int codeuse2=4;
unsigned int tick_1=0;
unsigned int tick_2=0;
int cmd=0;
const int frequence=50;
float consigne_moteur_nombre_tours_par_seconde=5;
float kp=1;


void compteur(){
  tick_1++;
  //tick_2++;  a faire 
  }
  
void asservissement(){
  int frequence_codeuse=frequence*tick_1;
  float nb_tour_par_sec=(float)frequence_codeuse/(float)20/(float)48;
  float erreur =consigne_moteur_nombre_tours_par_seconde-nb_tour_par_sec;
 
  tick_1=0;
  cmd=kp*erreur;
  if (cmd<0)cmd=0;
  else if (cmd>255)cmd=255;
  analogWrite(motor1_enablePin,255-cmd);
  // Serial.println(tick_1);
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
 

  // set enablePin high so that motor can turn on:
  analogWrite(motor1_enablePin, 170);
  analogWrite(motor2_enablePin, 170);
delay(5000);
attachInterrupt(codeuse1,compteur,CHANGE);
timer.setInterval(1000/frequence,asservissement);

}


void loop() {
  timer.run();
  delay(10);
}
