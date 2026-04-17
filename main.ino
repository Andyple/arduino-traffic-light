/*
 * main.ino
 * Central controller for the Multi-Mode Traffic Light.
 * Manages mode switching and hardware initialization.
 */

// --- Global Pin Definitions ---
// Define pins for LEDs
const int RED_LED = 2;
const int YELLOW_LED = 3;
const int GREEN_LED = 4;

// Define pins for Mode Selection Buttons
const int BTN_STANDARD = 5;
const int BTN_SENSOR = 6;
const int BTN_REMOTE = 7;

// --- State Management ---
enum Mode {
  STANDARD,
  SENSOR,
  REMOTE
};

Mode currentMode = STANDARD;

void setup() {
  // 1. Initialize Serial communication
  
  // 2. Set pin modes for LEDs
  
  // 3. Set pin modes for Buttons (use INPUT_PULLUP if needed)
  
  // 4. Initialize sensors (Ultrasonic, IR) - setup code can be in their respective files
  setupSensorMode();
  setupRemoteMode();
  
  Serial.println("System Initialized. Default Mode: STANDARD");
}

void loop() {
  // 1. Poll buttons to check for mode change
  checkModeButtons();

  // 2. Execute the logic for the current mode
  switch (currentMode) {
    case STANDARD:
      runStandardMode();
      break;
    case SENSOR:
      runSensorMode();
      break;
    case REMOTE:
      runRemoteMode();
      break;
  }
}

void checkModeButtons() {
  // Logic to read buttons and update 'currentMode'
}
