import serial
import time

print("Opening port and forcing ESP32 to wake up...")
ser = serial.Serial('/dev/ttyUSB0', 115200)

# Manually toggle DTR and RTS to release the ESP32's reset pin
ser.setDTR(False)
ser.setRTS(False)
time.sleep(0.1)
ser.setDTR(True)
ser.setRTS(True)

print("Waiting 2 seconds for boot...")
time.sleep(2)

print("Sending clear command...")
ser.write(b'$C\n')

response = ser.read(1)
print(f"Success! Vbuddy replied with: {response.decode()}")
ser.close()
