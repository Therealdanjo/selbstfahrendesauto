#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>

SoftwareSerial s(3,1);

const char* ssid = "Autosepp";
const char* password = "sepp1234";


int ledPin = D4;
int ledPin1 = D3;
int ledPin2 = D2;
int ledPin3 = D1;

WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, LOW);
 
  // Mit Wifi verbinden
  Serial.print("Verbinden mit: "); 
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi verbunden");
 
  // Start des Servers
  server.begin();
  Serial.println("Server gestartet");
 
  // Print the IP address
  Serial.print("Diese URL zum Verbinden aufrufen: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Prüfen, ob sich ein Client verbunden hat
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Warten auf Daten vom Client
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Erste Zeile des Requests lesen
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  //int value = LOW;
  if (request.indexOf("/forward") != -1)  {
    switchAll();
    digitalWrite(ledPin, HIGH);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("/backward") != -1)  {
    switchAll();
    digitalWrite(ledPin1, HIGH);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("/right") != -1)  {
    switchAll();
    digitalWrite(ledPin2, HIGH);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("/left") != -1)  {
    switchAll();
    digitalWrite(ledPin3, HIGH);
    //s.write(123);
    //value = HIGH;
  }

  
  // Anfrage zurücksenden
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body>");
  client.println("<p>Steuerung AutoSepp</p>");
  client.println("<div class=\"div-buttons\">");

  //forward
  client.println("<a href=\"/forward\">");
  client.println("<button id=\"b1\">");
  client.println("<p><</p>");
  client.println("</button>");
  client.println("</a>");
  client.println("<div class=\"div-buttons2\">");

  //left
  client.println("<a href=\"/left\">");
  client.println("<button id=\"b2\">");
  client.println("<p><</p>");
  client.println("</button>");
  client.println("</a>");

  //stop
  client.println("<a href=\"#\">");
  client.println("<button id=\"b2\"></button>");
  client.println("</a>");

  //right
  client.println("<a href=\"/right\">");
  client.println("<button id=\"b3\"><p>></p></button>");
  client.println("</a>");
  client.println("</div>");

  //backwards
  client.println("<a href=\"/backward\">");
  client.println("<button id=\"b4\">");
  client.println("<p>></p>");
  client.println("</button>");
  client.println("</a>");
  client.println("</div>");
  client.println("<style>");
  client.println("body {display: grid;place-items: center;background-color: #42c549;}");
  client.println("body > p{font-size: 70px;color: #ff2f52;font-family: Verdana, Geneva, Tahoma, sans-serif;}");
  client.println("button {width: 200px;height: 200px;font-size: 100px;background-color: Transparent;background-repeat: no-repeat;border: none;cursor: pointer;overflow: hidden;}");
  client.println(".div-buttons {display: flex;flex-direction: column;width: 200px;}");
  client.println(".div-buttons2 {display: flex; flex-direction: row;}");
  client.println("#b1 {position: relative;right: -100px;top: 200px;transform: rotate(90deg);}");
  client.println("#b1 p { position: relative;top: -220px;}");
  client.println("#b4 {position: relative;right: -100px;top: -200px;transform: rotate(90deg);}");
  client.println("#b4 p {position: relative;top: -220px;}");
  client.println("#b3 {position: relative;position: relative;}");
  client.println("#b3 p {position: relative;top: -220px;}");
  client.println("#b2 {position: relative;right: 100px;}");
  client.println("#b2 p {position: relative;top: -220px;}");
  client.println("<style>");
  client.println("");
  client.println("");
  client.println("");
  
  
  
 
  //client.print("Die LED ist: ");
 
  //if(value == HIGH) {
  //  client.print("Aus");
  //} else {
  //  client.print("An");
  //}
  
  client.println("<a href=\"/forward\"\"><button>Forward</button></a>");
  client.println("<a href=\"/backward\"\"><button>Backward</button></a>");
  client.println("<a href=\"/right\"\"><button>Right</button></a>");
  client.println("<a href=\"/left\"\"><button>Left</button></a>");
  
  client.println("</body>");


  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client trennen");
  Serial.println("");
 
}

void switchAll(){
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
}
