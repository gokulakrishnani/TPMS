#include "HX711.h"
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
RH_ASK rf_driver;


int ledPin1 = 3;

int ledPin2 = 4;
HX711 scale;

void setup() {
  rf_driver.init();

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("welcome");
  Serial.println("Initializing the scale");
   lcd.setCursor(0,0);
   lcd.print("Welcome");
   delay(200);
    lcd.setCursor(0,1); //sets cursor to column 0, row 0
    lcd.print("Initializing....");
    delay(400);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  scale.begin(A1, A0);

  scale.set_scale(2280.f);    // set the scale to convert units to kPa
  scale.tare();    // reset the scale to 0

  Serial.println("Readings:");
}

void loop() {
  uint8_t buf[24];
  uint8_t buflen = sizeof(buf);

  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen))
  {
    Serial.print("Air pressure: ");
    Serial.println((char*)buf);
    Serial.println("   ");                           
    lcd.setCursor(0,1);
    lcd.print((char*)buf);    
    lcd.setCursor(0,0); //sets cursor to column 0, row 0
    lcd.print("Air Pressure :"); //prints label
    lcd.setCursor(5,1);
    lcd.print("Psi"); //prints label after value
    lcd.print("        "); //to clear the display after large values or negatives

    float pressure = atof((char*)buf);

    if (pressure < 35) {
      // Turn on the LED
      digitalWrite(ledPin1, HIGH);
      delay(600);
      digitalWrite(ledPin1, LOW);
      delay(600);
    }
  }
  }           
