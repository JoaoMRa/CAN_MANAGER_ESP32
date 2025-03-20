import time
from machine import Pin, SPI
import mcp2515

class CAN_Manager:
    def __init__(self, cs_pin):
        self.cs = Pin(cs_pin, Pin.OUT)
        self.spi = SPI(1, baudrate=10000000, polarity=0, phase=0)
        self.can = mcp2515.MCP2515(self.spi, self.cs)
        self.ignition_on = False
        self.ignition_start_time = 0

    def begin(self):
        return self.can.begin()

    def check_ignition(self):
        data = self.send_can_request(0x01, 1)
        if data:
            ignition = data[0] & 0x01
            if ignition and not self.ignition_on:
                self.ignition_start_time = time.ticks_ms()
                self.ignition_on = True
            elif not ignition:
                self.ignition_on = False
            return ignition
        return False

    def get_engine_run_time(self):
        if self.ignition_on:
            return time.ticks_ms() - self.ignition_start_time
        return 0

    def read_dtc(self):
        data = self.send_can_request(0x03, 2)
        if data:
            return (data[0] << 8) | data[1]
        return None

    def get_rpm(self):
        data = self.send_can_request(0x0C, 2)
        if data:
            return ((data[0] * 256) + data[1]) / 4
        return -1

    def get_speed(self):
        data = self.send_can_request(0x0D, 1)
        return data[0] if data else -1

    def get_engine_temperature(self):
        data = self.send_can_request(0x05, 1)
        return data[0] - 40 if data else -1

    def get_fuel_level(self):
        data = self.send_can_request(0x2F, 1)
        return (data[0] * 100) / 255.0 if data else -1

    def send_can_request(self, pid, length):
        request = [0x02, 0x01, pid, 0, 0, 0, 0, 0]
        self.can.send(0x7DF, request)
        
        timeout = time.ticks_ms() + 1000
        while time.ticks_ms() < timeout:
            if self.can.available():
                return self.can.read()
        return None
