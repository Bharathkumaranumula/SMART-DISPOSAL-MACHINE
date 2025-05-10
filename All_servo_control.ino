#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <string.h>

#define TRIG 2 // Ultrasonic sensor trigger pin
#define ECHO 3 // Ultrasonic sensor echo pin (PWM)
#define SERVO_FREQ 60 // PCA9685 PWM frequency for servos

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

#define SERVO_BR 0   // Servo for Biodegradable & Recyclable waste bin
#define SERVO_BNR 1  // Servo for Biodegradable & Non-Recyclable waste bin
#define SERVO_NBR 2  // Servo for Non-Biodegradable & Recyclable waste bin
#define SERVO_NBNR 3 // Servo for Non-Biodegradable & Non-Recyclable waste bin
#define SERVO_LOW 4  // Lower servo in sorting mechanism
#define SERVO_UP 5   // Upper servo in sorting mechanism
#define SERVO_MID_FLAP 6 // Middle flap servo for waste direction
#define SERVO_LID 7  // Servo for Lid

#define PROXIMITY_OPEN 22  // To open main Lid
#define PROXIMITY_CLOSE 23 // To close main Lid

long updated_sensor_values[4] = {0, 0, 0, 0};

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("ARDUINO2");

    // Initialize PCA9685
    pca.begin();
    pca.setPWMFreq(SERVO_FREQ);
    
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(PROXIMITY_OPEN, INPUT);
    pinMode(PROXIMITY_CLOSE, INPUT);
    
    setServoPosition(SERVO_LOW, 0);
    setServoPosition(SERVO_UP, 0);
    setServoPosition(SERVO_MID_FLAP, 0);
    setServoPosition(SERVO_BR, 0);
    setServoPosition(SERVO_BNR, 0);
    setServoPosition(SERVO_NBR, 0);
    setServoPosition(SERVO_NBNR, 180);
    setServoPosition(SERVO_LID, 0);
}

void setServoPosition(int servo, int angle) {
    int pulse = map(angle, 0, 180, 150, 600); // Convert angle to PWM pulse width
    pca.setPWM(servo, 0, pulse);
}

void update_distance(int n) {
    delay(2000);
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    long duration = pulseIn(ECHO, HIGH);
    long distance = duration * 0.034 / 2;
    updated_sensor_values[n] = distance;
}

void disk_reset() {
    setServoPosition(SERVO_LOW, 0);
    setServoPosition(SERVO_UP, 0);
}

void bio_ren() {
    setServoPosition(SERVO_UP, 45);
    delay(1000);
    setServoPosition(SERVO_LOW, 0);
    delay(1000);
    setServoPosition(SERVO_MID_FLAP, 90);
    delay(3000);
    setServoPosition(SERVO_MID_FLAP, 0);
    delay(1000);
}

void bio_nonren() {
    setServoPosition(SERVO_UP, 170);
    delay(1000);
    setServoPosition(SERVO_LOW, 0);
    delay(1000);
    setServoPosition(SERVO_MID_FLAP, 90);
    delay(3000);
    setServoPosition(SERVO_MID_FLAP, 0);
    delay(1000);
}

void nonbio_ren() {
    setServoPosition(SERVO_UP, 170);
    delay(1000);
    setServoPosition(SERVO_LOW, 90);
    delay(1000);
    setServoPosition(SERVO_MID_FLAP, 90);
    delay(3000);
    setServoPosition(SERVO_MID_FLAP, 0);
    delay(1000);
}

void nonbio_nonren() {
    setServoPosition(SERVO_UP, 135);
    delay(1000);
    setServoPosition(SERVO_LOW, 180);
    delay(1000);
    setServoPosition(SERVO_MID_FLAP, 90);
    delay(3000);
    setServoPosition(SERVO_MID_FLAP, 0);
    delay(1000);
}

void flush_trash_to_external_bin() {
    setServoPosition(SERVO_BR, 90);
    setServoPosition(SERVO_BNR, 90);
    setServoPosition(SERVO_NBR, 80);
    setServoPosition(SERVO_NBNR, 180);
    delay(4000);
    setServoPosition(SERVO_BR, 0);
    setServoPosition(SERVO_BNR, 0);
    setServoPosition(SERVO_NBR, 0);
    setServoPosition(SERVO_NBNR, 0);
}

void close_lid() {
    setServoPosition(SERVO_LID, 0);
    delay(1000);
}

void open_lid() {
    setServoPosition(SERVO_LID, 90);
    delay(1000);
}

void loop()
{
  // Check for serial commands
  if (Serial.available() > 0)
  {
    String message = Serial.readStringUntil('\n');
    message.trim(); // Remove whitespace

    // Process different commands
    if (message.equals("BR"))
    {
      bio_ren();
      update_distance(0);
      disk_reset();
    }
    else if (message.equals("BNR"))
    {
      bio_nonren();
      update_distance(1);
      disk_reset();
    }
    else if (message.equals("NBR"))
    {
      nonbio_ren();
      update_distance(2);
      disk_reset();
    }
    else if (message.equals("NBNR"))
    {
      nonbio_nonren();
      update_distance(3);
      disk_reset();
    }
    else if (message.equals("GETD")) // Request bin levels
    {
      // Send all sensor values as comma-separated string
      Serial.print(updated_sensor_values[0]);
      Serial.print(",");
      Serial.print(updated_sensor_values[1]);
      Serial.print(",");
      Serial.print(updated_sensor_values[2]);
      Serial.print(",");
      Serial.println(updated_sensor_values[3]);
    }
    else if (message.equals("FLUSH")) // Empty all bins
    {
      flush_trash_to_external_bin();
    }
    else if (message.equals("RESTART"))
    {
      while (true)
      {
        if ((digitalRead(PROXIMITY_OPEN) == HIGH) && (digitalRead(PROXIMITY_CLOSE) == LOW))
        {
          open_lid();
        }
        else if ((digitalRead(PROXIMITY_CLOSE) == HIGH) && (digitalRead(PROXIMITY_OPEN) == LOW))
        {
          close_lid();
          break;
        }
        delay(1000);}
        }
}
}