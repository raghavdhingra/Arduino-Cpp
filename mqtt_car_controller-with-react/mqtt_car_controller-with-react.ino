/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Dhingra"
#define WLAN_PASS       "alohomora"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "mqtt.raghavdhingra.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "raghavdhingra"
#define AIO_KEY         "qwerty1234"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe upButton = Adafruit_MQTT_Subscribe(&mqtt, "car/remote/up");
Adafruit_MQTT_Subscribe leftButton = Adafruit_MQTT_Subscribe(&mqtt, "car/remote/left");
Adafruit_MQTT_Subscribe rightButton = Adafruit_MQTT_Subscribe(&mqtt, "car/remote/right");
Adafruit_MQTT_Subscribe downButton = Adafruit_MQTT_Subscribe(&mqtt, "car/remote/down");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&upButton);
  mqtt.subscribe(&leftButton);
  mqtt.subscribe(&rightButton);
  mqtt.subscribe(&downButton);
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  int currentBtn = 0;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &upButton) {
      currentBtn = 0;
      if (strcmp((char *)upButton.lastread,"0") == 0) {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      } else if (strcmp((char *)upButton.lastread,"1") == 0) {
        digitalWrite(D0, HIGH);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, HIGH);
      } else {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      }
    }
    if (subscription == &leftButton) {
      if (strcmp((char *)leftButton.lastread,"0") == 0) {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      } else if (strcmp((char *)leftButton.lastread,"1") == 0) {
        if (currentBtn == 0) {
          digitalWrite(D0, HIGH);
          digitalWrite(D1, LOW);
        } else {
          digitalWrite(D0, LOW);
          digitalWrite(D1, HIGH);
        }
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      } else {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      }
    }
    if (subscription == &rightButton) {
      if (strcmp((char *)rightButton.lastread,"0") == 0) {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      } else if (strcmp((char *)rightButton.lastread,"1") == 0) {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        if (currentBtn == 0) {
          digitalWrite(D2, LOW);
          digitalWrite(D3, HIGH);
        } else {
          digitalWrite(D2, HIGH);
          digitalWrite(D3, LOW);
        }
      } else {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      }
    }
    if (subscription == &downButton) {
      currentBtn = 1;
      if (strcmp((char *)downButton.lastread,"0") == 0) {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      } else if (strcmp((char *)downButton.lastread,"1") == 0) {
        digitalWrite(D0, LOW);
        digitalWrite(D1, HIGH);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, LOW);
      } else {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
      }
    }
  }

  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
  digitalWrite(LED_BUILTIN, LOW);

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
  digitalWrite(LED_BUILTIN, HIGH);
}
