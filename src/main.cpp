#include <Arduino.h>
#include"Class_DS18B20.h"

unsigned long Break_10s = 0;                                //Variable fuer Dinge die alle 1s ausgefuehrt werden
TSensorArray PortSD2(9);
TSensorArray PortSD3(10);

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  if(millis()>Break_10s)
  {
    Break_10s = millis() + 10000;
    PortSD2.StartConversion();
    PortSD3.StartConversion();
    if(!PortSD2.GetSensorCount())
     Serial.print("Port SD2 No Sensor found\n");
    if(!PortSD3.GetSensorCount())
     Serial.print("Port SD3 No Sensor found\n");
  }
  if(PortSD2.Loop())
  {
    for(int i = 0; i < PortSD2.GetSensorCount(); i++)
    {
      if(PortSD2.GetSensor(i)->NewValueAvailable())
      {
        Serial.print("New Value for Sensor ");
        Serial.print(PortSD2.GetSensor(i)->getName());
        Serial.print(": ");
        Serial.print(PortSD2.GetSensor(i)->getTempC());
        Serial.println(" °C"); 
      }
    }
  }
  if(PortSD3.Loop())
  {
    for(int i = 0; i < PortSD3.GetSensorCount(); i++)
    {
      if(PortSD3.GetSensor(i)->NewValueAvailable())
      {
        Serial.print("Neuer Temp Wert für Sensor ");
        Serial.print(PortSD3.GetSensor(i)->getName());
        Serial.print(": ");
        Serial.print(PortSD3.GetSensor(i)->getTempC());
        Serial.println(" °C"); 
      }
    }
  }
}