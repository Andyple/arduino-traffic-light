/*
 * mode_sensor.ino
 * Logic for the traffic light with car detection using an ultrasonic sensor.
 * Cycles Green -> Yellow -> Red when a car leaves.
 */

// Pins for Ultrasonic Sensor
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int DETECTION_THRESHOLD = 20; // 20 cm

// Timing constants
const unsigned long SENSOR_YELLOW_DURATION = 2000; 

enum SensorState {
  SENS_RED,
  SENS_GREEN,
  SENS_YELLOW
};

static SensorState currentSensState = SENS_RED;
static unsigned long sensStateStartTime = 0;
static Mode lastModeInSensor = REMOTE; // To detect mode entry

/**
 * Updates the physical LEDs based on the current sensor state.
 */
void updateSensorLEDs() {
  digitalWrite(RED_LED,    (currentSensState == SENS_RED)    ? HIGH : LOW);
  digitalWrite(GREEN_LED,  (currentSensState == SENS_GREEN)  ? HIGH : LOW);
  digitalWrite(YELLOW_LED, (currentSensState == SENS_YELLOW) ? HIGH : LOW);
}

void setupSensorMode() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  currentSensState = SENS_RED;
}

/**
 * Returns true if an object is within the threshold.
 */
bool isCarDetected() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) return false;
  
  int distance = duration * 0.034 / 2;
  return (distance > 0 && distance < DETECTION_THRESHOLD);
}

void runSensorMode() {
  unsigned long currentTime = millis();
  bool carPresent = isCarDetected();

  // Detect mode entry
  if (lastModeInSensor != currentMode) {
    lastModeInSensor = currentMode;
    // Reset to RED when entering mode for safety, or keep current state
    updateSensorLEDs();
    Serial.println("Sensor Mode Active: RED (waiting for car)");
  }

  switch (currentSensState) {
    case SENS_RED:
      if (carPresent) {
        currentSensState = SENS_GREEN;
        updateSensorLEDs();
        Serial.println("Car detected! Light: GREEN");
      }
      break;

    case SENS_GREEN:
      if (!carPresent) {
        currentSensState = SENS_YELLOW;
        sensStateStartTime = currentTime;
        updateSensorLEDs();
        Serial.println("Car left. Light: YELLOW");
      }
      break;

    case SENS_YELLOW:
      // If a car returns during yellow, go back to green
      if (carPresent) {
        currentSensState = SENS_GREEN;
        updateSensorLEDs();
        Serial.println("Car returned during yellow. Light: GREEN");
      } 
      else if (currentTime - sensStateStartTime >= SENSOR_YELLOW_DURATION) {
        currentSensState = SENS_RED;
        updateSensorLEDs();
        Serial.println("Timeout. Light: RED");
      }
      break;
  }

  delay(50); // Small delay to stabilize sensor readings
}
