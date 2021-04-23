#include <esp8266wifi.h>
#include <wificlient.h>
#include <esp8266wifimulti.h> 
#include <esp8266mdns.h>
#include <esp8266webserver.h>

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);

void handleRoot();              
void handleRequest();
void handleNotFound();

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(5, 0);
  digitalWrite(4, 0);
  
  analogWriteRange(100);
  analogWrite(0, 0);

  Serial.begin(9600);
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("Dhingra", "alohomora");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/command", HTTP_POST, handleRequest);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  return;
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); // Listen for HTTP requests from clients
  return;
}

void handleRoot() {  // When URI / is requested, send a standard web page 
  server.send(200, "text/html", "Wi-fi Remote Control Example");
  return;
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
  return;
}

void handleRequest() { // If a POST request is made to URI /command
  // Validate parameters
  if(!server.hasArg("pin") || !server.hasArg("value") || server.arg("pin") == NULL || server.arg("value") == NULL) { 
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
  
  // Get the parameters: pin and value
  String temp = "";
  temp = server.arg("pin"); 
  int pin = temp.toInt();
  temp = server.arg("value"); 
  int value = temp.toInt();

  Serial.println(pin);
  Serial.println(value);
  if (pin >= 0 && pin < 17 && value >= 0 && value <= 100) {
    if (pin == 0) {
      analogWrite(pin, value);
    } else {
      digitalWrite(pin, value);
    }
  }
  server.send(200, "text/html", "Wi-fi Remote Control Example");
  return;
}
