int soundSensor = 2;
int led = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(soundSensor,OUTPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int statusSensor = digitalRead(soundSensor);
  if (statusSensor == 1) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
