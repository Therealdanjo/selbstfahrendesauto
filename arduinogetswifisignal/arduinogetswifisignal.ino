
 //i galb irgendepes mit tx und rx, keine ahung

int forwardPin = A8;
int backwardPin = A9;
int rightPin = A10;
int leftPin = A11;

int changemodusPin = A13;
int mode = 1;

int forwardValue = 0;
int backwardValue = 0;
int rightValue = 0;
int leftValue = 0;

const int sensorlinksTrigger = 22;
const int sensorlinksEcho = 23;
const int sensormitteTrigger = 24;
const int sensormitteEcho = 25;
const int sensorrechtsTrigger = 26;
const int sensorrechtsEcho = 27;
const int sensoruntenTrigger = 28;
const int sensoruntenEcho = 29;

boolean obgas = true;

int cm = 0;

void setup() {

  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin

  pinMode(sensormitteTrigger, OUTPUT);
  pinMode(sensormitteEcho, INPUT);
  pinMode(sensorlinksTrigger, OUTPUT);
  pinMode(sensorlinksEcho, INPUT);
  pinMode(sensorrechtsTrigger, OUTPUT);
  pinMode(sensorrechtsEcho, INPUT);
  pinMode(sensoruntenTrigger, OUTPUT);
  pinMode(sensoruntenEcho, INPUT);
  
  Serial.begin(9600);
    
}

void loop() {

  forwardValue = analogRead(forwardPin);
  backwardValue = analogRead(backwardPin);
  rightValue = analogRead(rightPin);
  leftValue = analogRead(leftPin);

/*
  Serial.println("serr");
  Serial.println(forwardValue);
  Serial.println(backwardValue);
  Serial.println(rightValue);
  Serial.println(leftValue);
*/

  if (mode == 1) {
    halbmanual();
  } else if (mode == 2) {
    automatisch();
  } else {
    Serial.println("den modus gebs gornet");
  }

  if (ison(changemodusPin)) {
    mode = 2;
  } else {
    mode = 1;  
  }

  delay(500);

}

boolean ison(int value) {
  
  if (value > 100) {
    return true;
  } else {
    return false;
  }
  
}

void halbmanual () {
  if (ison(leftValue)) {
    Serial.println("iatz links");
    left();
  } else if (ison(rightValue)) {
    Serial.println("iatz rechts");
    right();
  } else if (ison(backwardValue)) {
    Serial.println("iatz zrug");
    back();
  } else if (ison(forwardValue)) {
    cm = getdistance(sensormitteTrigger, sensormitteEcho);
    Serial.println("iatz vor");
    Serial.print(cm);
    Serial.print("cm");
    Serial.print('\n');
    if (cm > 10) {
      forward();
    } else {
      stopp();
    }
  } else {
    stopp();
  }
}

void automatisch() {
  
  if (getdistance(sensorlinksTrigger, sensorlinksEcho) < 20 or getdistance(sensormitteTrigger, sensormitteEcho) < 25 or getdistance(sensorrechtsTrigger, sensorrechtsEcho) < 20 or getdistance(sensoruntenTrigger, sensoruntenEcho) > 10) {
      obgas = false;
      changedir();
  }else{
    forward();
    obgas=true;
  }
  
}

void changedir(){
  while(!obgas){ //richtung wechseln
    if(getdistance(sensoruntenTrigger, sensoruntenEcho) > 10){
      for(int i=0;i<100; ++i ){
        back();  
      }
    }else if (getdistance(sensorlinksTrigger, sensorlinksEcho) < 20) {
      if(getdistance(sensorlinksTrigger, sensorlinksEcho) < 20 and getdistance(sensorrechtsTrigger, sensorrechtsEcho) < 20){
        for(int i=0; i<100; ++i){
          back();
        }
        for(int j=0; j<100; ++j){
          left();  
        }
      }else if(getdistance(sensorrechtsTrigger, sensorrechtsEcho) < getdistance(sensorlinksTrigger, sensorlinksEcho)){
         left();
      }else{
        right();
      }
    }else if(getdistance(sensormitteTrigger, sensormitteEcho) < 25){
      if(getdistance(sensorlinksTrigger, sensorlinksEcho) < getdistance(sensorrechtsTrigger, sensorrechtsEcho)){
        right();  
      }else{
        left(); 
      }
    }else if (getdistance(sensorrechtsTrigger, sensorrechtsEcho) <20){
      if(getdistance(sensorlinksTrigger, sensorlinksEcho) < 20 and getdistance(sensorrechtsTrigger, sensorrechtsEcho) < 20){
        for(int i=0; i<100; ++i){
          back();  
        }
        for(int j=0; j<100; ++j){
          right();  
        }
      }else if(getdistance(sensorrechtsTrigger, sensorrechtsEcho) < getdistance(sensorlinksTrigger, sensorlinksEcho)){
         left();
      }else{
        right();
      }
    }
    obgas=true;
  }
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

int getdistance (int trigger,int echo) {
  long duration, cm;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
