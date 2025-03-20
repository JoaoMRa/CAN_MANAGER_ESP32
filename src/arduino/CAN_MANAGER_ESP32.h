#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

class CAN_Manager {
public:
    CAN_Manager(int csPin);
    bool begin();
    bool checkIgnition();
    unsigned long getEngineRunTime();
    bool readDTC(uint32_t &dtcCode);
    int getRPM();
    int getSpeed();
    float getEngineTemperature();
    float getFuelLevel();
    
private:
    int _csPin;
    MCP_CAN _can;
    unsigned long ignitionStartTime;
    bool isIgnitionOn;
    
    bool sendCANRequest(uint16_t pid, uint8_t *buffer, uint8_t len);
};

#endif // CAN_MANAGER_H
