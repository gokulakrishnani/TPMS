//transmitter d12
#include <RadioHead.h>
#include "Wire.h" 

#include <RH_ASK.h> // Include dependant SPI Library
#include <SPI.h>
const int pressureInput = A0; 
const float SensorOffset = 102.0;

RH_ASK rf_driver;

// Create Amplitude Shift Keying Object RH_ASK rf_driver;

void setup()

{
  Serial.begin(9600);
  rf_driver.init();
}
// Initialize ASK Object rf_driver.init();


   void loop()
{
   float sensorValue = (analogRead(A0)-SensorOffset)/100.0; 
   
   float sensor=sensorValue*10; 
   float air=sensor-24; 
   char str[20];
   dtostrf(air, 4, 2, str);
   rf_driver.send((uint8_t *)str, strlen(str));
   rf_driver.waitPacketSent();
   delay(100);
}

  
       //ttransmitted code
