/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int dtime = 500;

void setup() {
  analogWrite(6, 100);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void sChar(String ch) {
  lcd.print(ch);
  delay(dtime);
}
void rm(int pos) {
  lcd.setCursor(pos, 1);
  lcd.print(" ");
  delay(dtime);
}

void loop() {
  delay(2000);
  sChar("S");
  sChar("H");
  sChar("I");
  sChar("V");
  sChar("A");
  sChar("Y");
  sChar(" ");
  
  sChar("I");
  sChar("S");
  sChar(" ");
  
  sChar("B");
  sChar("E");
  sChar("S");
  sChar("T");

  lcd.setCursor(0,1);
  sChar("S");
  sChar("P");
  sChar("E");
  sChar("A");
  sChar("K");
  sChar("E");
  sChar("R");
  rm(6);
  rm(5);
  rm(4);
  rm(3);
  rm(2);
  rm(1);
  rm(0);

  lcd.setCursor(0,1);
  sChar("C");
  sChar("T");
  sChar("O");
  rm(3);
  rm(2);
  rm(1);
  rm(0);


  lcd.setCursor(0,1);
  sChar("M");
  sChar("E");
  sChar("N");
  sChar("T");
  sChar("O");
  sChar("R");
  rm(5);
  rm(6);
  rm(4);
  rm(3);
  rm(2);
  rm(1);
  rm(0);

  
  lcd.setCursor(0,1);
  sChar("G");
  sChar("I");
  sChar("T");
  sChar("H");
  sChar("U");
  sChar("B");
  sChar(" ");
  sChar("M");
  sChar("A");
  sChar("S");
  sChar("T");
  sChar("E");
  sChar("R");

  delay(1000);

  sChar("X");
  sChar("D");
  
  delay(10000);
}
