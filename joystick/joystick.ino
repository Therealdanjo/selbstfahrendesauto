
int vzport = A4;
int rlprot = A5;
int vzvalue = 0;
int rlvalue = 0;

void setup() {

  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
  Serial.begin(9600);
}

void loop() {

  vzvalue = analogRead(vzport);
  rlvalue = analogRead(rlprot);

/*
  Serial.print("vor Zurueck = ");
  Serial.print(vzvalue);
  Serial.print('\n');

  Serial.print("rechts Links = ");
  Serial.print(rlvalue);
  Serial.print('\n');
*/
  if (rlvalue < 10) {
    Serial.print("iatz links");
    Serial.print('\n');
    left();
  } else if (rlvalue > 1000) {
    Serial.print("iatz rechts");
    Serial.print('\n');
    right();
  } else if (vzvalue < 10) {
    Serial.print("iatz zrug");
    Serial.print('\n');
    back();
  } else if (vzvalue > 1000) {
    Serial.print("iatz vor");
    Serial.print('\n');
    forward();
  } else {
    stopp();
  }

  delay(100);

} 


void forward(){
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);
}

void back(){
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);
}

void left(){
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);
}

void right(){
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);
}

void stopp(){
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}
