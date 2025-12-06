# -*- coding: utf-8 -*-
"""
Created on Wed Nov 26 16:15:40 2025

@author: 13125
"""

import serial
import os
import time
from serial import SerialException


SERIAL_PORT = "COM4"   
BAUD_RATE = 9600
MP3_PATH = r"C:\Users\13125\Downloads\Main_Sound_411.mp3"
COOLDOWN = 5 


def main():
    print(f"Opening serial port {SERIAL_PORT} at {BAUD_RATE} baud...")
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    except SerialException as e:
        print(f"❌ Could not open {SERIAL_PORT}. Is the Arduino connected?")
        print(e)
        return

    print("✅ Connected. Listening for 'PLAY' from Arduino...")

    last_play_time = 0  

    try:
        while True:
            line = ser.readline().decode(errors='ignore').strip()
            if line:
                print("Serial:", line)

            if line == "PLAY":
                now = time.time()
                if now - last_play_time >= COOLDOWN:
                    print("Trigger received → opening audio in default player...")
                    try:
                        os.startfile(MP3_PATH)  
                        last_play_time = now
                    except Exception as e:
                        print("❌ Error trying to open audio file:", e)
                else:
                    print("In cooldown period, skipping replay.")
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        ser.close()

if __name__ == "__main__":
    main()
