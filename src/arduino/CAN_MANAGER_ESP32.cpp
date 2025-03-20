#include "CAN_Manager.h"

CAN_Manager::CAN_Manager(int csPin) : _csPin(csPin), _can(csPin) {
    isIgnitionOn = false;
    ignitionStartTime = 0;
}

bool CAN_Manager::begin() {
    if (_can.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
        _can.setMode(MCP_NORMAL);
        return true;
    }
    return false;
}

bool CAN_Manager::checkIgnition() {
    uint8_t buffer[8];
    if (sendCANRequest(0x01, buffer, 1)) {
        bool ignition = buffer[0] & 0x01;
        if (ignition && !isIgnitionOn) {
            ignitionStartTime = millis();
            isIgnitionOn = true;
        } else if (!ignition) {
            isIgnitionOn = false;
        }
        return ignition;
    }
    return false;
}

unsigned long CAN_Manager::getEngineRunTime() {
    if (isIgnitionOn) {
        return millis() - ignitionStartTime;
    }
    return 0;
}

bool CAN_Manager::readDTC(uint32_t &dtcCode) {
    uint8_t buffer[8];
    if (sendCANRequest(0x03, buffer, 2)) {
        dtcCode = (buffer[0] << 8) | buffer[1];
        return true;
    }
    return false;
}

int CAN_Manager::getRPM() {
    uint8_t buffer[8];
    if (sendCANRequest(0x0C, buffer, 2)) {
        return ((buffer[0] * 256) + buffer[1]) / 4;
    }
    return -1;
}

int CAN_Manager::getSpeed() {
    uint8_t buffer[8];
    if (sendCANRequest(0x0D, buffer, 1)) {
        return buffer[0];
    }
    return -1;
}

float CAN_Manager::getEngineTemperature() {
    uint8_t buffer[8];
    if (sendCANRequest(0x05, buffer, 1)) {
        return buffer[0] - 40;
    }
    return -1;
}

float CAN_Manager::getFuelLevel() {
    uint8_t buffer[8];
    if (sendCANRequest(0x2F, buffer, 1)) {
        return (buffer[0] * 100) / 255.0;
    }
    return -1;
}

bool CAN_Manager::sendCANRequest(uint16_t pid, uint8_t *buffer, uint8_t len) {
    uint8_t data[8] = { 0x02, 0x01, pid, 0, 0, 0, 0, 0 };
    _can.sendMsgBuf(0x7DF, 0, 8, data);

    unsigned long timeout = millis() + 1000;
    while (millis() < timeout) {
        if (_can.checkReceive() == CAN_MSGAVAIL) {
            _can.readMsgBuf(&len, buffer);
            return true;
        }
    }
    return false;
}
