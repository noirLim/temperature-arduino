#include <LiquidCrystal_I2C.h>
#include <math.h>

const int col = 16;
const int row = 2;

LiquidCrystal_I2C lcd(0x27, col, row);

int sensorPin = A0;
int redLed = 7;
int blueLed = 6;

double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
  Temp = Temp - 273.15;  // Convert Kelvin to Celcius
  return Temp;
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  int readVal = analogRead(sensorPin);
  double temp = Thermistor(readVal);

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temp) + " C");

  lcd.setCursor(0, 1);

  if (temp <= 30) {
    digitalWrite(blueLed, HIGH);
    lcd.print("Status: Cold");

  } else {
    digitalWrite(blueLed, LOW);
  }

  if (temp >= 31) {
    lcd.clear();
    digitalWrite(redLed, HIGH);
    lcd.print("Status: Hot");
  } else {
    digitalWrite(redLed, LOW);
  }

  delay(1000);
}