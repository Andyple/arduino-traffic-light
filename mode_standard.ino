/*
 * mode_standard.ino
 * Logic for the standard timed traffic light cycle.
 */

// Durations for each light state in milliseconds
const unsigned long RED_DURATION = 5000;
const unsigned long GREEN_DURATION = 5000;
const unsigned long YELLOW_DURATION = 2000;

// State management for standard mode
enum StandardState {
  STD_RED,
  STD_GREEN,
  STD_YELLOW
};

static StandardState currentStdState = STD_RED;
static unsigned long lastStdSwitchTime = 0;
static Mode lastModeInStandard = REMOTE; // Used to detect mode entry

/**
 * Updates the physical LEDs based on the current standard state.
 */
void updateStandardLEDs() {
  digitalWrite(RED_LED,    (currentStdState == STD_RED)    ? HIGH : LOW);
  digitalWrite(GREEN_LED,  (currentStdState == STD_GREEN)  ? HIGH : LOW);
  digitalWrite(YELLOW_LED, (currentStdState == STD_YELLOW) ? HIGH : LOW);
}

/**
 * Initialization for standard mode.
 */
void setupStandardMode() {
  currentStdState = STD_RED;
  lastStdSwitchTime = millis();
}

/**
 * Main loop for standard mode logic.
 * Cycles through GREEN -> YELLOW -> RED using non-blocking timing.
 */
void runStandardMode() {
  unsigned long currentTime = millis();

  // Detect if we just switched into this mode from another one
  if (lastModeInStandard != currentMode) {
    lastModeInStandard = currentMode;
    updateStandardLEDs();
    lastStdSwitchTime = currentTime; // Reset timer on entry
    Serial.println("Standard Mode Active: RED");
  }

  // Determine current state duration
  unsigned long currentDuration = 0;
  switch (currentStdState) {
    case STD_RED:    currentDuration = RED_DURATION;    break;
    case STD_GREEN:  currentDuration = GREEN_DURATION;  break;
    case STD_YELLOW: currentDuration = YELLOW_DURATION; break;
  }

  // Check if it's time to switch to the next state
  if (currentTime - lastStdSwitchTime >= currentDuration) {
    // State transition logic
    if (currentStdState == STD_RED) {
      currentStdState = STD_GREEN;
      Serial.println("Standard Mode: GREEN");
    } else if (currentStdState == STD_GREEN) {
      currentStdState = STD_YELLOW;
      Serial.println("Standard Mode: YELLOW");
    } else if (currentStdState == STD_YELLOW) {
      currentStdState = STD_RED;
      Serial.println("Standard Mode: RED");
    }

    lastStdSwitchTime = currentTime;
    updateStandardLEDs();
  }
}
