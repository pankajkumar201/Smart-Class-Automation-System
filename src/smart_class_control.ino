Description:
An occupancy-based classroom automation system implemented in Python.
The system controls classroom devices using PIR sensor input,
includes auto-off delay for stability, and a manual override feature
for real-world usability.
"""

import RPi.GPIO as GPIO
import time

# GPIO pin configuration
PIR_SENSOR_PIN = 17
DEVICE_PIN = 27
MANUAL_BUTTON_PIN = 22

# Auto-off delay (seconds)
OFF_DELAY = 10

# System state variables
last_motion_time = 0
device_state = False
manual_override = False

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(PIR_SENSOR_PIN, GPIO.IN)
GPIO.setup(DEVICE_PIN, GPIO.OUT)
GPIO.setup(MANUAL_BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

print("Smart Class Automation System Started")

try:
    while True:
        current_time = time.time()

        # Manual override logic
        if GPIO.input(MANUAL_BUTTON_PIN) == GPIO.LOW:
            manual_override = not manual_override
            print("Manual Override:", "ON" if manual_override else "OFF")
            time.sleep(0.3)  # debounce

        # PIR sensor logic
        if GPIO.input(PIR_SENSOR_PIN):
            last_motion_time = current_time
            if not manual_override:
                device_state = True
                print("Occupancy detected → Device ON")

        # Auto-off delay logic
        if not manual_override:
            if device_state and (current_time - last_motion_time > OFF_DELAY):
                device_state = False
                print("No occupancy → Device OFF (Auto Delay)")

        # Output control
        GPIO.output(DEVICE_PIN, GPIO.HIGH if device_state else GPIO.LOW)

        time.sleep(0.2)

except KeyboardInterrupt:
    print("System Stopped")

finally:
    GPIO.cleanup()
