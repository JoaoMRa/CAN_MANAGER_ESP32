# CAN_Manager_ESP32

Library for interacting with **CAN Bus** on **ESP32**, designed for vehicle diagnostics and real-time monitoring. This library allows **reading vehicle data**, **detecting ignition state**, **measuring engine runtime**, and **retrieving diagnostic trouble codes (DTCs)**.

## 🚀 Features
- Detects **vehicle ignition** state.
- Tracks **engine runtime**.
- Reads **RPM**, **speed**, **engine temperature**, and **fuel level**.
- Retrieves **Diagnostic Trouble Codes (DTCs)**.
- Compatible with **Arduino (C++)** and **MicroPython**.

## 📦 Installation

### For **Arduino**
1. Download or clone this repository.
2. Copy `CAN_Manager.h` and `CAN_Manager.cpp` into your **Arduino project**.
3. Include the library in your **sketch**:

```cpp
#include "CAN_MANAGER_ESP32.h"
CAN_Manager_ESP32 can(5); // CS pin
For MicroPython
Upload CAN_MANAGER_ESP32.py to your ESP32 using Thonny or mpy-cross.
Import the library in your MicroPython code:
```
```python
from CAN_MANAGER_ESP32 import CAN_Manager_ESP32
can = CAN_MANAGER_ESP32(5)
```

## 📖 Usage Examples
### 🟢 Basic Example (Arduino)
```cpp
#include "CAN_MANAGER_ESP32.h"

CAN_MANAGER_ESP32 can(5);

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
```
### 🟢 Basic Example (MicroPython)
```python

from CAN_MANAGER_ESP32 import CAN_MANAGER_ESP32
import time

can = CAN_MANAGER_ESP32(5)

while True:
    print("RPM:", can.get_rpm())
    print("Speed:", can.get_speed())
    print("Engine Temp:", can.get_engine_temperature())
    print("Fuel Level:", can.get_fuel_level())
    print("Engine Runtime:", can.get_engine_run_time())
    time.sleep(1)
```
##🛠 Function Reference
Here’s a table of the main functions available in the CAN_Manager library:

| **Function**              | **Description**                                      |
|---------------------------|------------------------------------------------------|
| `begin()`                 | Initializes CAN communication.                       |
| `checkIgnition()`         | Returns `true` if the vehicle ignition is on.       |
| `getEngineRunTime()`      | Returns the time (in ms) the engine has been running. |
| `readDTC(uint32_t &dtc)`  | Reads the Diagnostic Trouble Code (DTC).            |
| `getRPM()`                | Reads the engine RPM.                               |
| `getSpeed()`              | Reads the vehicle speed in km/h.                    |
| `getEngineTemperature()`  | Reads the engine temperature in °C.                 |
| `getFuelLevel()`          | Reads the fuel level in %.                          |

## 🔗 Resources
### GitHub Repository: CAN_Manager_ESP32
### MicroPython: micropython.org
### Arduino ESP32: arduino.cc
### CAN Protocol: Wikipedia
## ✉️ Maintainer: João Moreira
