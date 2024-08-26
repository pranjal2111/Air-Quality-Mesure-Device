#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "rgb_lcd.h"

const int airQualityPin = A0;  // MQ135 sensor output pin
const int lcdRS = SCL;  // LCD RS pin
const int lcdEN = SDA;  // LCD EN pin
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 255;
const int colorB = 255;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(airQualityPin, INPUT);  // Set air quality pin as input
  // Initialize LCD display (if using)
  lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);

  pinMode(lcdRS, OUTPUT);
  pinMode(lcdEN, OUTPUT);
}

void loop() {
  int airQualityValue = analogRead(airQualityPin);  // Read air quality value
  float airQuality = map(airQualityValue, 0, 1023, 0, 100);  // Map value to percentage

  // Print air quality value to serial monitor
  Serial.print("Air Quality:");
  Serial.print(airQuality);
  Serial.println("%");

  // Display air quality value on LCD (if using)
  lcdClear();
  lcd.setCursor(0, 0);
  lcd.print("airQuality:");
  lcd.setCursor(0, 1);
  lcd.print(airQuality);
  lcd.print("%");

  delay(1000);  // Wait 1 second before taking next reading
}

// LCD display functions (if using)
void lcdClear() {
  digitalWrite(lcdRS, HIGH);
  digitalWrite(lcdEN, LOW);
  delay(1);
  digitalWrite(lcdEN, HIGH);
}

void lcdPrint(String text) {
  digitalWrite(lcdRS, HIGH);
  for (int i = 0; i < text.length(); i++) {
    digitalWrite(lcdEN, HIGH);
    delay(1);
    digitalWrite(lcdEN, LOW);
  }
}