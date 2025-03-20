#include "CAN_Manager_ESP32.h"

CAN_Manager_ESP32 can(5);

void setup() {
    Serial.begin(115200);
    can.begin();
}

void loop() {
    Serial.print("RPM: ");
    Serial.println(can.getRPM());
    Serial.print("Speed: ");
    Serial.println(can.getSpeed());
    Serial.print("Engine Temp: ");
    Serial.println(can.getEngineTemperature());
    Serial.print("Fuel Level: ");
    Serial.println(can.getFuelLevel());
    Serial.print("Engine Runtime: ");
    Serial.println(can.getEngineRunTime());
    
    delay(1000);
}