const int echoPin1 = 6; // Echo Pin of Ultrasonic Sensor
const int pingPin1 = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = 4; // Echo Pin of Ultrasonic Sensor
const int pingPin2 = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin3 = 2; // Echo Pin of Ultrasonic Sensor
const int pingPin3 = 22; // Trigger Pin of Ultrasonic Sensor
const int echoPin4 = 24; // Echo Pin of Ultrasonic Sensor
const int pingPin4 = 26; // Trigger Pin of Ultrasonic Sensor


boolean obgas = true;
long duration1,duration2,duration3, duration4, cm1, cm2, cm3, cm4;

void setup() {
  //Sensor 1
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin

  pinMode(pingPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(pingPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(pingPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  Serial.begin(9600); // Starting Serial Terminal

} 

void loop(){
  if(obgas) {
    forward();
  } else {
    changedir();
  }
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);

  digitalWrite(pingPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);

  digitalWrite(pingPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);

  cm1 = microsecondsToCentimeters(duration1);
  //Serial.print("cm1: ");
  //Serial.print(cm1);
  
  cm2 = microsecondsToCentimeters(duration2);
  //Serial.print("cm2: ");
  //Serial.print(cm2);
  
  cm3 = microsecondsToCentimeters(duration3);
  //Serial.print("cm3: ");
  //Serial.print(cm3);
  
  cm4 = microsecondsToCentimeters(duration4);
  //Serial.print("cm3: ");
  //Serial.print(cm3);
  
  Serial.println();
  delay(100);

  
  if (cm1 < 15 or cm2 < 20 or cm3 < 15 or cm4 > 20) {
    obgas = false;
    //changedir();
  }else{
    obgas=true;
  }
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void changedir(){
  while(true){ //richtung wechseln
    if (cm1 < 15) {
      obgas = false;
      left();
    } else if(cm2 < 20){
      if(cm1<cm2){
        obgas = false;
        left();  
      }else{
        obgas=false;
        right();    
      }
    } else if (cm3 <15){
        obgas=false;
        right();
    } else if(cm4 >20){
      for(int i=0; i<100; ++i){
        back();  
      }
      
    }
    
    obgas=true;
    break;
  }
}

void forward(){
  Serial.print("noch vorne gsepplt");
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
  Serial.print("noch links gsepplt");
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);
}

void right(){
  Serial.print("noch rechts gsepplt");
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);
