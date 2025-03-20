from CAN_MANAGER_ESP32 import CAN_MANAGER_ESP32
import time

can = CAN_Manager(cs_pin=5)

while True:
    print("RPM:", can.get_rpm())
    print("Speed:", can.get_speed())
    print("Engine Temp:", can.get_engine_temperature())
    print("Fuel Level:", can.get_fuel_level())
    print("Engine Runtime:", can.get_engine_run_time())
    time.sleep(1)
