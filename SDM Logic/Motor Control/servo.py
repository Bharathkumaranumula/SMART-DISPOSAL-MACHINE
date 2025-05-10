import RPi.GPIO as GPIO
import time

SERVO_PIN = 17  # GPIO17 (Pin 11)
GPIO.setmode(GPIO.BCM)
GPIO.setup(SERVO_PIN, GPIO.OUT)

pwm = GPIO.PWM(SERVO_PIN, 50)  # 50Hz PWM signal
pwm.start(0)


def set_angle(angle):
    duty_cycle = (angle / 18) + 2
    pwm.ChangeDutyCycle(duty_cycle)
    time.sleep(0.5)

try:
    while True:
        for angle in range(0, 181, 30):  # Move from 0° to 180° in steps
            set_angle(angle)
            print(f"Moved to {angle}°")
        time.sleep(1)

        for angle in range(180, -1, -30):  # Move back from 180° to 0°
            set_angle(angle)
            print(f"Moved to {angle}°")
        time.sleep(1)

except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()

