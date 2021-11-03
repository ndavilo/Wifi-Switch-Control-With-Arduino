

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//SSID and Password to your ESP Access Point
const char* ssid = "SWITCH01";
const char* password = "password1";

ESP8266WebServer server(80); //Server on port 80
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi SWITCH ON - OFF : </h1><br>
</a><br>
Click to turn <a href="AllSwitchOn" target="myIframe">ALL SWITCH ON</a><br>
</a><br>
Click to turn <a href="AllSwitchOff" target="myIframe">ALL SWITCH OFF</a><br>
</a><br>
Click to turn <a href="Switch1On" target="myIframe">SWITCH 1 ON</a><br>
</a><br>
Click to turn <a href="Switch1Off" target="myIframe">SWITCH 1 OFF</a><br>
</a><br>
Click to turn <a href="Switch2On" target="myIframe">SWITCH 2 ON</a><br>
</a><br>
Click to turn <a href="Switch2Off" target="myIframe">SWITCH 2 OFF</a><br>
</a><br>
Click to turn <a href="Switch3On" target="myIframe">SWITCH 3 ON</a><br>
</a><br>
Click to turn <a href="Switch3Off" target="myIframe">SWITCH 3 OFF</a><br>
</a><br>
Click to turn <a href="Switch4On" target="myIframe">SWITCH 4 ON</a><br>
</a><br>
Click to turn <a href="Switch4Off" target="myIframe">SWITCH 4 OFF</a><br>
</a><br>
ALL SWITCH STATE:<iframe name="myIframe" width="100" height="50" frameBorder="5"><br>
<hr>
<a href="https://">david.com</a>
</center>
 
</body>
</html>
)=====";

#define LED 2
#define LED2 5
#define LED3 4
#define LED4 12


//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleLEDonAll() { 
 Serial.println("LED on page");
 digitalWrite(LED,LOW); //LED is connected in reverse
 digitalWrite(LED2,LOW);
 digitalWrite(LED3,LOW);
 digitalWrite(LED4,LOW);
 server.send(200, "text/html", "ALL ON"); //Send ADC value only to client ajax request
}
 
void handleLEDoffAll() { 
 Serial.println("LED off page");
 digitalWrite(LED,HIGH); //LED off
 digitalWrite(LED2,HIGH);
 digitalWrite(LED3,HIGH);
 digitalWrite(LED4,HIGH);
 server.send(200, "text/html", "ALL OFF"); //Send ADC value only to client ajax request
}

void handleLEDon1() { 
 Serial.println("LED on page");
 digitalWrite(LED,LOW); //LED is connected in reverse
 server.send(200, "text/html", "1 ON"); //Send ADC value only to client ajax request
}

void handleLEDoff1() { 
 Serial.println("LED off page");
 digitalWrite(LED,HIGH); //LED off
 server.send(200, "text/html", "1 OFF"); //Send ADC value only to client ajax request
}

void handleLEDon2() { 
 Serial.println("LED on page");
 digitalWrite(LED2,LOW); //LED is connected in reverse
 server.send(200, "text/html", "2 ON"); //Send ADC value only to client ajax request
}

void handleLEDoff2() { 
 Serial.println("LED off page");
 digitalWrite(LED2,HIGH); //LED off
 server.send(200, "text/html", "2 OFF"); //Send ADC value only to client ajax request
}
void handleLEDon3() { 
 Serial.println("LED on page");
 digitalWrite(LED3,LOW); //LED is connected in reverse
 server.send(200, "text/html", "3 ON"); //Send ADC value only to client ajax request
}

void handleLEDoff3() { 
 Serial.println("LED off page");
 digitalWrite(LED3,HIGH); //LED off
 server.send(200, "text/html", "3 OFF"); //Send ADC value only to client ajax request
}
void handleLEDon4() { 
 Serial.println("LED on page");
 digitalWrite(LED4,LOW); //LED is connected in reverse
 server.send(200, "text/html", "4 ON"); //Send ADC value only to client ajax request
}

void handleLEDoff4() { 
 Serial.println("LED off page");
 digitalWrite(LED4,HIGH); //LED off
 delay(4000);
 digitalWrite(LED4,LOW);
 delay(7000);
 digitalWrite(LED4,HIGH);
 server.send(200, "text/html", "4 OFF"); //Send ADC value only to client ajax request
}

//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
  delay(7000);
  pinMode(LED,OUTPUT); 
  //Power on LED state off
  digitalWrite(LED,HIGH);
  pinMode(LED2,OUTPUT); 
  digitalWrite(LED2,LOW);
  pinMode(LED3,OUTPUT); 
  digitalWrite(LED3,HIGH);
  pinMode(LED4,OUTPUT); 
  digitalWrite(LED4,HIGH);
 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/AllSwitchOn", handleLEDonAll); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/AllSwitchOff", handleLEDoffAll);
  server.on("/Switch1On", handleLEDon1); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/Switch1Off", handleLEDoff1);
  server.on("/Switch2On", handleLEDon2); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/Switch2Off", handleLEDoff2);
  server.on("/Switch3On", handleLEDon3); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/Switch3Off", handleLEDoff3);
  server.on("/Switch4On", handleLEDon4); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/Switch4Off", handleLEDoff4);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//===============================================================
//                     LOOP
//===============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
