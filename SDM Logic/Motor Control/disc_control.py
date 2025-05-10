import serial
import time
 
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1) # /dev/ttyUSB0 to be changed with our serial port
time.sleep(2)  # Waiting for connection to establish

while True:
    try:
        user_input = input("Enter message to send('exit' to quit): ") #input to be given here
        
        if user_input.lower()=='exit':
            print("Exiting...")
            break 
        
        # Sending input to Arduino
        ser.write((user_input + "\n").encode('utf-8'))  
        print("Sent:",user_input)

        # Waiting and reading response
        time.sleep(1)
        response = ser.readline().decode('utf-8').strip()
        
        if response:
            print("Received from Arduino:", response)

    except Exception as e:
        print("Error:", e)
        break


