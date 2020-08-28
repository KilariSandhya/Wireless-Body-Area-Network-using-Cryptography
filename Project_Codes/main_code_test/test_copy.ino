#include <Wire.h>
#include "Protocentral_MAX30205.h"
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000

MAX30205 tempSensor;

long count=0;

PulseOximeter pox;

uint32_t tsLastReport = 0;

int address_temp = 72; //binary equivalent is 01001000(0x48)
int address_pulse = 87; //binary equivalent is 01010111(0x57)

String Name = String("Name: *** ");
String age = String("Age: ** ");
String contact = String("Contact: ********** ");
String temp_sensor_value;
String Pulse_sensor_value;

void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup(){

Serial.begin(9600); //this creates the Serial Monitor
Wire.begin(); //this creates a Wire object
tempSensor.begin();

Serial.print("Initializing pulse oximeter...");
if (!pox.begin()) {
       Serial.println("FAILED");
       for(;;);
   } else {
       Serial.println("SUCCESS");
   }

pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop(){
Wire.beginTransmission(address_temp);
Wire.write(0);
Wire.endTransmission();
Wire.requestFrom(address_temp, 1);

while(Wire.available() == 0);
 if(++count == 1275){
  float temp = tempSensor.getTemperature(); // read temperature for every 100ms
  Serial.print(temp ,2);
  Serial.println("'C" );
  float fahrenheit = temp * 9.00/5.00 + 32.00;
  Serial.print(fahrenheit ,2);
  Serial.println("'F" );
  count = 0;
 }
//delay(1000);

Wire.beginTransmission(address_pulse);
Wire.write(0);
Wire.endTransmission();
Wire.requestFrom(address_pulse, 1);

while(Wire.available() == 0);

  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
       Serial.print("Heart rate:");
       Serial.print(pox.getHeartRate());
       Serial.print("bpm / SpO2:");
       Serial.print(pox.getSpO2());
       Serial.println("%");
       tsLastReport = millis();
  }
  
//delay(2000);
}
