#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>

SoftwareSerial s(3,1);

const char* ssid = "a";
const char* password = "hoi12345";


int ledPin = D4;
int ledPin1 = D3;
int ledPin2 = D2;
int ledPin3 = D1;

int manuell = D5;
int automatisch = D6;
int controller = D7;

int switchManuell = 0;

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
  
  pinMode(manuell, OUTPUT);
  //digitalWrite(manuell, LOW);
  pinMode(automatisch, OUTPUT);
  digitalWrite(automatisch, LOW);
  pinMode(controller, OUTPUT);
  digitalWrite(controller, LOW);
 
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
  if (request.indexOf("forward") != -1)  {
    switchAll();
    digitalWrite(ledPin, HIGH);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("backward") != -1)  {
    switchAll();
    digitalWrite(ledPin1, HIGH);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("right") != -1)  {
    switchAll();
    digitalWrite(ledPin2, HIGH);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("left") != -1)  {
    switchAll();
    digitalWrite(ledPin3, HIGH);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("stop") != -1)  {
    switchAll();
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("manuell") != -1)  {
    switchAll();
    switchAllModes();
    digitalWrite(manuell, HIGH);
    //analogWrite(manuell, 200);
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("automatisch") != -1)  {
    switchAll();
    switchAllModes();
    digitalWrite(automatisch, HIGH); 
    //s.write(123);
    //value = HIGH;
  }
  if (request.indexOf("controller") != -1)  {
    switchAll();
    switchAllModes();
    digitalWrite(controller, HIGH); 
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
  
  /*client.println("<p>Steuerung AutoSepp</p>");
  

  //switchManuell
  client.println("<a href=\"/switchManuell\">");
  client.println("<button id=\"switchManuell\">");
  client.println("<p>Switch</p>");
  client.println("</button>");
  client.println("</a>");

  //Stop
  client.println("<a href=\"/stop\">");
  client.println("<button id=\"stop\">");
  client.println("<p>Stop</p>");
  client.println("</button>");
  client.println("</a>");

  
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
  client.println("</div>");*/
  //client.println("    <div class=cable></div>    <div class=controller>        <div class=centerBlue>            <div class=centerLeft>            </div>            <div class=centerRight></div>        </div>        <div class=centerStart>            <div class=SLeft></div>            <div class=SRight></div>        </div>        <div class=centerSelect>            <div class=SLeft></div>            <div class=SRight></div>        </div>        <div class=controllerLeft>            <div class=circle></div>            <div class=crossCenter>                <a href=forward>                    <button class=crossTop>                    </button>                </a>                <a href=backward>                    <button class=crossBottom>                    </button>                </a>                <a href=left>                    <button class=crossLeft>                    </button>                </a>                <a href=right>                    <button class=crossRight>                    </button>                </a>                <a href=stop>                    <button class=crossCircle>                    </button>                </a>            </div>        </div>        <div class=controllerRight>            <div class=backButton1Center>                <a href=>                    <button class=cornerLeft1>                    </button>                </a>                <a href=>                    <div class=cornerRight1>                    </div>                </a>            </div>            <div class=backButton2Center>                <div class=cornerLeft2></div>                <div class=cornerRight2></div>            </div>        </div>    </div>");
  //client.println("    <div class=cable></div>    <div class=controller>        <div class=centerBlue>            <div class=centerLeft>            </div>            <div class=centerRight></div>        </div>        <div class=centerStart>            <div class=SLeft></div>            <div class=SRight></div>        </div>        <div class=centerSelect>            <div class=SLeft></div>            <div class=SRight></div>        </div>        <div class=controllerLeft>            <div class=circle></div>            <div class=crossCenter>                <a href=forward>                    <button class=crossTop>                    </button>                </a>                <a href=backward>                    <button class=crossBottom>                    </button>                </a>                <a href=left>                    <button class=crossLeft>                    </button>                </a>                <a href=right>                    <button class=crossRight>                    </button>                </a>                <a href=stop>                    <button class=crossCircle>                    </button>                </a>            </div>        </div>        <div class=controllerRight>            <div class=backButton1Center>                <a href=switchManuell>                    <button class=cornerLeft1>                    </button>                </a>                <a href=>                    <div class=cornerRight1>                    </div>                </a>            </div>            <div class=backButton2Center>                <div class=cornerLeft2></div>                <div class=cornerRight2></div>            </div>        </div>    </div>");
  client.println("    <div class=cable></div>    <div class=controller>        <div class=centerBlue>            <div class=centerLeft>            </div>            <div class=centerRight></div>        </div>        <div class=centerStart>            <div class=SLeft></div>            <div class=SRight></div>        </div>        <div class=centerSelect>            <div class=SLeft></div>            <div class=SRight></div>        </div>        <div class=controllerLeft>            <div class=circle></div>            <div class=crossCenter>                <a href=forward>                    <button class=crossTop>                    </button>                </a>                <a href=backward>                    <button class=crossBottom>                    </button>                </a>                <a href=left>                    <button class=crossLeft>                    </button>                </a>                <a href=right>                    <button class=crossRight>                    </button>                </a>                <a href=stop>                    <button class=crossCircle>                    </button>                </a>            </div>        </div>        <div class=controllerRight>            <div class=backButton1Center>                <a href=manuell>                    <button class=cornerLeft1>                        M                    </button>                </a>                <a href=automatisch>                    <button class=cornerRight1>                        A                    </button>                </a>            </div>            <div class=backButton2Center>                <a href=controller>                    <button class=cornerLeft2>                        C                    </button>                </a>                <div class=cornerRight2></div>            </div>        </div>    </div>");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("<style>");
  client.println("* {            margin: auto;            padding: 0;            -webkit-box-sizing: border-box;            box-sizing: border-box;        }        body {            background-color: #FEFEFE;        }        .controller {            margin-top: 100px;            height: 200px;            width: 400px;            background-color: #E6E6E6;            position: relative;            box-shadow: 15px 15px 15px rgba(0, 0, 0, 0.2);        }        .controllerLeft {            height: 250px;            width: 250px;            background-color: #E6E6E6;            position: absolute;            border-radius: 100%;            margin-left: -125px;            box-shadow: -15px 8px 15px rgba(0, 0, 0, 0.2);        }        .controllerRight {            height: 250px;            width: 250px;            background-color: #B8B8B8;            position: relative;            border-radius: 100%;            margin-right: -125px;            border: solid 15px rgba(230, 230, 230, 1);            box-shadow: 15px 8px 15px rgba(0, 0, 0, 0.2);        }        .circle {            height: 150px;            width: 150px;            background-color: #E6E6E6;            position: absolute;            border-radius: 100%;            border: solid 5px rgba(184, 184, 184, 1);            margin-left: 42px;            margin-top: 52px;        }        .crossCenter {            background-color: #333333;            width: 35px;            height: 35px;            margin-top: 110px;            margin-left: 100px;            position: relative;        }        .crossCircle {            background-color: #292929;            width: 25px;            height: 25px;            position: absolute;            border-radius: 100%;            margin-top: 5px;            margin-left: 5px;        }        .crossTop {            background-color: #333333;            width: 35px;            height: 35px;            position: absolute;            border-radius: 15%;            margin-top: -30px;        }        .crossBottom {            background-color: #333333;            width: 35px;            height: 35px;            position: absolute;            border-radius: 15%;            margin-top: 30px;        }        .crossLeft {            background-color: #333333;            width: 35px;            height: 35px;            position: absolute;            border-radius: 15%;            margin-left: -30px;        }        .crossRight {            background-color: #333333;            width: 35px;            height: 35px;            position: absolute;            border-radius: 15%;            margin-left: 30px;        }        .centerBlue {            position: absolute;            width: 50px;            height: 20px;            margin-left: 175px;            margin-top: 30px;            background-color: #0099FF;        }        .centerLeft {            position: absolute;            width: 20px;            height: 20px;            margin-left: -10px;            margin-top: 0px;            background-color: #0099FF;            border-radius: 100%;        }        .centerRight {            position: absolute;            width: 20px;            height: 20px;            margin-left: 40px;            margin-top: 0px;            background-color: #0099FF;            border-radius: 100%;        }        .backButton1Center {            position: absolute;            width: 80px;            height: 50px;            background-color: #E6E6E6;            -webkit-transform: rotate(-30deg);            margin-top: 60px;            margin-left: 45px;        }        .backButton2Center {            position: absolute;            width: 80px;            height: 50px;            background-color: #E6E6E6;            -webkit-transform: rotate(-30deg);            margin-top: 115px;            margin-left: 90px;        }        .cornerLeft1 {            position: absolute;            width: 50px;            height: 50px;            background-color: #00B800;            border-radius: 100%;            margin-left: -20px;            border: solid 5px rgba(230, 230, 230, 1)        }        .cornerRight1 {            position: absolute;            width: 50px;            height: 50px;            background-color: #6699FF;            border-radius: 100%;            margin-left: 60px;            border: solid 5px rgba(230, 230, 230, 1)        }        .cornerLeft2 {            position: absolute;            width: 50px;            height: 50px;            background-color: #CFCF00;            border-radius: 100%;            margin-left: -20px;            border: solid 5px rgba(230, 230, 230, 1)        }        .cornerRight2 {            position: absolute;            width: 50px;            height: 50px;            background-color: #7D230D;            border-radius: 100%;            margin-left: 60px;            border: solid 5px rgba(230, 230, 230, 1)        }        .centerStart {            background-color: #B8B8B8;            position: absolute;            height: 35px;            width: 10px;            margin-left: 180px;            margin-top: 110px;            -webkit-transform: rotate(20deg);        }        .centerSelect {            background-color: #B8B8B8;            position: absolute;            height: 35px;            width: 10px;            margin-left: 205px;            margin-top: 110px;            -webkit-transform: rotate(20deg);        }        .SLeft {            background-color: #B8B8B8;            position: absolute;            border-radius: 100%;            height: 10px;            width: 10px;            margin-top: 30px;        }        .SRight {            background-color: #B8B8B8;            position: absolute;            border-radius: 100%;            height: 10px;            width: 10px;            margin-top: -5px;        }        .cable {            background-color: black;            width: 10px;            height: 150px;            position: absolute;            margin-left: 49.7%;            margin-top: -100px;            box-shadow: 7px 8px 15px rgba(0, 0, 0, 0.2);        }");
  client.println("<style>");
  
  
  
 
  //client.print("Die LED ist: ");
 
  //if(value == HIGH) {
  //  client.print("Aus");
  //} else {
  //  client.print("An");
  //}
  
  client.println("</body>");


  
  client.println("</html>");
 
  delay(100);
  Serial.println("Client trennen");
  Serial.println("");
 
}

void switchAllModes(){
    digitalWrite(automatisch, LOW); 
    digitalWrite(manuell, LOW); 
    digitalWrite(controller, LOW); 
}

void switchAll(){
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
}
