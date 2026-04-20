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

// --- Function Prototypes (Helper for compilation outside Arduino IDE) ---
void setupSensorMode();
void setupRemoteMode();
void runStandardMode();
void runSensorMode();
void runRemoteMode();

void setup() {
  // 1. Initialize Serial communication
  Serial.begin(9600);
  
  // 2. Set pin modes for LEDs
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  // 3. Set pin modes for Buttons
  pinMode(BTN_STANDARD, INPUT_PULLUP);
  pinMode(BTN_SENSOR, INPUT_PULLUP);
  pinMode(BTN_REMOTE, INPUT_PULLUP);
  
  // 4. Initialize specific modes
  setupSensorMode();
  setupRemoteMode();
  
  Serial.println("Traffic Light System Initialized.");
  Serial.println("Current Mode: STANDARD");
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
  if (digitalRead(BTN_STANDARD) == LOW) {
    if (currentMode != STANDARD) {
      currentMode = STANDARD;
      Serial.println("Switched to STANDARD Mode");
      delay(200); // Debounce
    }
  } else if (digitalRead(BTN_SENSOR) == LOW) {
    if (currentMode != SENSOR) {
      currentMode = SENSOR;
      Serial.println("Switched to SENSOR Mode");
      delay(200); // Debounce
    }
  } else if (digitalRead(BTN_REMOTE) == LOW) {
    if (currentMode != REMOTE) {
      currentMode = REMOTE;
      Serial.println("Switched to REMOTE Mode");
      delay(200); // Debounce
    }
  }
}
