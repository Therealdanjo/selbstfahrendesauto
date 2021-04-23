
int ledPin = 13;
int data;
char character;
int start_flag = 0;

void setup() {
  Serial.begin(921600); 
  pinMode(ledPin, OUTPUT); 
}
void loop() {
  if(Serial.available() > 0){
    character = (char) Serial.read();
    if(character == 's') {
      start_flag = 1;
    }
    if(character == 't') {
      start_flag = 0;
    }
  }
  if (start_flag == 1) {
    Serial.print(data); //data that was acquired by internal ADC
  }

}
