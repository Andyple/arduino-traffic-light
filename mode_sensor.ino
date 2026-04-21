/*
 * mode_sensor.ino
 * Logic for the traffic light with car detection using an ultrasonic sensor.
 */

// Define pins for Ultrasonic Sensor (ECHO_PIN 10, TRIG_PIN 9)
// Note: Ensure TRIG_PIN and ECHO_PIN do not conflict with other modes.
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int DETECTION_THRESHOLD = 20; // x = 20 cm away

void setupSensorMode() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void runSensorMode() {
  // 1. Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2. Measure echo time
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // 3. Calculate distance in cm
  int distance = duration * 0.034 / 2;

  // 4. Logic for car detection:
  if (distance > 0 && distance < DETECTION_THRESHOLD) {
    // Car detected: Turn GREEN
    Serial.print("Object detected! Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  } else {
    // No car: Stay RED
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
  
  delay(100); // Small delay to avoid flooding the sensor
}
