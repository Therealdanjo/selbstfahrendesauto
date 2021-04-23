
 //i galb irgendepes mit tx und rx, keine ahung

int forwardPin = A1;
int backwardPin = A2;
int rightPin = A3;
int leftPin = A4;

int forwardValue = 0;
int backwardValue = 0;
int rightValue = 0;
int leftValue = 0;


void setup() {
  
  Serial.begin(9600);
    
}

void loop() {

  forwardValue = analogRead(forwardPin);
  backwardValue = analogRead(backwardPin);
  rightValue = analogRead(rightPin);
  leftValue = analogRead(leftPin);

/*
  Serial.println(forwardValue);
  Serial.println(backwardValue);
  Serial.println(rightValue);
  Serial.println(leftValue);
*/
  if (ison(forwardValue)) {
    Serial.println("forward");
  }
  if (ison(backwardValue)) {
    Serial.println("backward");
  }
  if (ison(rightValue)) {
    Serial.println("right");
  }
  if (ison(leftValue)) {
    Serial.println("left");
  }

  delay(500);

}

boolean ison(int value) {
  
  if (value > 200) {
    return true;
  } else {
    return false;
  }
  
}
