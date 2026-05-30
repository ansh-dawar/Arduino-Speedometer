#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

#define SENSOR_1_PIN 2
#define SENSOR_2_PIN 3

const float distanceBetweenSensors = 0.02;   // 2 cm

unsigned long startTime;
unsigned long stopTime;

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Speed Gun");
  delay(1000);

  lcd.clear();
  lcd.print("Scanning...");
}

void loop() {

  // wait for object at sensor 1
  if (digitalRead(SENSOR_1_PIN) == LOW) {

    startTime = micros();

    // wait for sensor 2
    while (digitalRead(SENSOR_2_PIN) == HIGH);

    stopTime = micros();

    unsigned long diff = stopTime - startTime;

    lcd.clear();

    // filter impossible values
    if (diff < 500 || diff > 300000) {
      lcd.print("Invalid");
    }
    else {
      float speed = (distanceBetweenSensors / (diff / 1000000.0)) * 3.6;

      lcd.setCursor(0, 0);
      lcd.print("Speed:");
      lcd.setCursor(0, 1);
      lcd.print(speed, 2);
      lcd.print(" km/h");
    }

    delay(1000);

    lcd.clear();
    lcd.print("Scanning...");

    // wait until hand leaves
    while (digitalRead(SENSOR_1_PIN) == LOW || digitalRead(SENSOR_2_PIN) == LOW);
    delay(200);
  }
}
