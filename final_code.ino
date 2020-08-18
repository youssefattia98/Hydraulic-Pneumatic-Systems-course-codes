#include <LiquidCrystal.h>

const int rs = 3, en = 4, d4 = 7, d5 = 8, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//defining pins
#define motor 13
#define piston 12

int pulses = 50;

float RPM = 0;
volatile int counter = 0;
unsigned long avgt = 0;
unsigned long t = 0;

char s = 0;

void pulse()
{
  counter++;
}

void setup() {
  t = millis();
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  pinMode(piston, OUTPUT);
  digitalWrite(motor, LOW);
  attachInterrupt(digitalPinToInterrupt(2), pulse, FALLING);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ABS SYSTEM");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Made by:");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Youssef Attia");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sohiab Salma");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Amr Mohamed");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ziad Ezzat");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Mohamed Ahmed");
  delay(500);
  lcd.clear();
  lcd.print("Ready to use");
}

void loop() {
  while (!Serial.available());
  s =  Serial.read();
  switch (s) {
    case 'o':
      Serial.println("ON");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motor power ON");
      digitalWrite(motor, HIGH);
      delay(1000);
      digitalWrite(motor, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motor power OFF");
      break;
    case 'f':
      Serial.println("OFF");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Breaking");
      digitalWrite(motor, LOW);
      do {
        digitalWrite(piston, HIGH);
        delay(pulses);
        digitalWrite(piston, LOW);
        delay(pulses);
        s =  Serial.read();
        avgt = millis() - t;
        if (avgt >= (1000)) {
          detachInterrupt(digitalPinToInterrupt(2));
          RPM = (counter * (60 / 12));
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("RPM: ");
          lcd.setCursor(0, 0);
          lcd.print(RPM);
          counter = 0;
          t = millis();
          attachInterrupt(digitalPinToInterrupt(2), pulse, FALLING);
          Serial.println(RPM);
          if (RPM <= 500)
            break;
        }
      } while (s != 'a');
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("0 RPM");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motor Stopped");
      delay(1500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Misson done");
      break;
  }
}
