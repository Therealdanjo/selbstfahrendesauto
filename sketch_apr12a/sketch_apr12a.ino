
int brakepinA = 9;
int brakepinB = 8;
int vorzurueckA = 12;
int vorzurueckB = 13;

void setup() {
  
  //Setup Channel A
  pinMode(vorzurueckA, OUTPUT); //Initiates Motor Channel A pin
  pinMode(brakepinA, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(vorzurueckB, OUTPUT); //Initiates Motor Channel A pin
  pinMode(brakepinB, OUTPUT);  //Initiates Brake Channel A pin
  
}

void loop(){

  //Motor A forward @ full speed
  digitalWrite(vorzurueckA, LOWä#ä#ä#
  ); //Establishes forward direction of Channel A
  digitalWrite(brakepinA, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B backward @ half speed
  digitalWrite(vorzurueckB, LOW);
  digitalWrite(brakepinB, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);
  
/*
  delay(3000);

  
  digitalWrite(brakepinA, HIGH);  //Engage the Brake for Channel A
  digitalWrite(brakepinB, HIGH);  //Engage the Brake for Channel B


  delay(1000);
  
  
  //Motor A forward @ full speed
  digitalWrite(vorzurueckA, LOW);  //Establishes backward direction of Channel A
  digitalWrite(brakepinA, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 123);    //Spins the motor on Channel A at half speed
  
  //Motor B forward @ full speed
  digitalWrite(vorzurueckB, HIGH); //Establishes forward direction of Channel B
  digitalWrite(brakepinB, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  
  
  delay(3000);
  
  
  digitalWrite(brakepinA, HIGH);  //Engage the Brake for Channel A
  digitalWrite(brakepinB, HIGH);  //Engage the Brake for Channel B
  
  
  delay(1000);

*/

}
