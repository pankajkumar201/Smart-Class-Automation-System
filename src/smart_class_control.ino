#define PIR_SENSOR_PIN 2      // PIR sensor input
#define DEVICE_PIN 8          // Relay or LED output

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(DEVICE_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Smart Class Automation System Started");
}

void loop() {
  int motionDetected = digitalRead(PIR_SENSOR_PIN);

  if (motionDetected == HIGH) {
    digitalWrite(DEVICE_PIN, HIGH);   // Turn ON device
    Serial.println("Occupancy detected: Device ON");
  } else {
    digitalWrite(DEVICE_PIN, LOW);    // Turn OFF device
    Serial.println("No occupancy: Device OFF");
  }

  delay(500); // Stability delay
}
