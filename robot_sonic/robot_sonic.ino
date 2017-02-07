// ___________________________________________________________________________________________________________________________

int motor1_enablePin = 3; //pwm
int motor1_in1Pin = 11;
int motor1_in2Pin = 12;

int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 9;
int motor2_in2Pin = 8;

int i;
int j;
int val;
int val2;
int redpin=0;
int redpin2=1;
int d;

// ___________________________________________________________________________________________________________________________


/*
 * Fonction qui fait quoi ?
 */
int distanceFunction(int val, int val2){
  int result;
  
  if (val<val2){ 
    result=val;
    }
  else{
    result=val2;
    }
  return result;
}


/*___________________________________________________________________________________________________________________________
 * ___________________________________________________________________________________________________________________________
 */
void setup() {
  // set all the other pins you're using as outputs:
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor1_enablePin, OUTPUT);
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
  pinMode(redpin,OUTPUT);
  pinMode(redpin2,OUTPUT);

  
    Serial.begin(9600);

  // set enablePin high so that motor can turn on:
  analogWrite(motor1_enablePin, 200);
  analogWrite(motor2_enablePin, 200);
}


void loop() {
  i=analogRead(redpin);
    val=(6762/(i-9))-4;
  j=analogRead(redpin2);
    val2=(6762/(j-9))-4;
  
  d=distanceFunction(val,val2);
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
     /*
     else
     {
     digitalWrite(motor1_in1Pin, LOW);   
     digitalWrite(motor1_in2Pin, HIGH);  
     digitalWrite(motor2_in1Pin, HIGH);   
     digitalWrite(motor2_in2Pin, LOW);  
     }
     */
     
     else
     {
     digitalWrite(motor1_in1Pin, LOW);   
     digitalWrite(motor1_in2Pin, HIGH);  
     digitalWrite(motor2_in1Pin, LOW);   
     digitalWrite(motor2_in2Pin, HIGH);  
 }
 
}
    

/*___________________________________________________________________________________________________________________________
 * ___________________________________________________________________________________________________________________________
 */

  
