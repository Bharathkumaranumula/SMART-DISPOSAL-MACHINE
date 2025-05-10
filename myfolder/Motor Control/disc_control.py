import serial
import time

# Replace '/dev/ttyUSB0' with your serial port
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2)  # Wait for connection to establish

while True:
    try:
        # Get user input
        user_input = input("Enter message to send (or 'exit' to quit): ")
        
        if user_input.lower() == 'exit':
            print("Exiting...")
            break  # Exit the loop
        
        # Send input to Arduino
        ser.write((user_input + "\n").encode('utf-8'))  
        print("Sent:", user_input)

        # Wait and read response
        time.sleep(1)
        response = ser.readline().decode('utf-8').strip()
        
        if response:
            print("Received from Arduino:", response)

    except Exception as e:
        print("Error:", e)
        break


