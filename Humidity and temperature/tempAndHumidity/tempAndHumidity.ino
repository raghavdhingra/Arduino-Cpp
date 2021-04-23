#include <dht.h>

#define dht_apin 7

dht DHT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("Values: \n\n");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_apin);
  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);
  Serial.print("Temperature: ");
  Serial.print(DHT.temperature);
  Serial.println("\n");
  delay(5000);
}
