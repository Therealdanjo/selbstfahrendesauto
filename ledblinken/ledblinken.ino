
boolean obein = false;
int inputPin = 10;
int outputPin = 13;

void setup() {  // initialize digital pin 13 as an output.
   pinMode(outputPin, OUTPUT);
   pinMode(inputPin, INPUT);
   Serial.begin(9600);
}

// the loop function runs over and over again forever

void loop() {
    if (digitalRead(inputPin) == HIGH) {
      Serial.println("knopf gedruckt");
      obein = true;
    } else if (digitalRead(inputPin) == LOW) {      //brauch GND damit olm low isch, sunst tuat olm awian komisch......
      Serial.println("iatz isch low"); 
    }

    if (digitalRead(inputPin) == HIGH && obein == true){
       //Serial.println("knopf noamol gedruckt");
       obein == false;
    }

    if(obein) {
      //Serial.println("led ein");
      digitalWrite(outputPin, HIGH); // turn the LED on (HIGH is the voltage level)
    } else {
      //Serial.println("led aus");
      digitalWrite(outputPin, LOW);
    }
      
}
