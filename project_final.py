import serial
import time
import os  # used to open audio with default media player

AUDIO_FILE = r"C:\Users\vishn\Downloads\audio_final.mp3"  # Your audio file path

# Connect to Arduino
ser = serial.Serial('COM5', 9600)
time.sleep(2)  # allow Arduino to reset

print("Listening for Arduino...")

while True:
    if ser.in_waiting:
        message = ser.readline().decode().strip()
        print("Received:", message)

        if message == "PLAY_AUDIO":
            print("Playing audio using default media player...")
            os.startfile(AUDIO_FILE)   # opens with default media player


