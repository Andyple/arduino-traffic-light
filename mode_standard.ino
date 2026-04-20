/*
 * mode_standard.ino
 * Logic for the standard timed traffic light cycle.
 */

// Timing for the standard mode (in milliseconds)
const long GREEN_TIME = 5000;
const long YELLOW_TIME = 2000;
const long RED_TIME = 5000;

static unsigned long lastUpdate = 0;
static int step = 0; // 0: Green, 1: Yellow, 2: Red

void runStandardMode() {
  unsigned long currentMillis = millis();
  
  // A simple timed sequence using a non-blocking timer
  if (step == 0) { // Green
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    if (currentMillis - lastUpdate >= GREEN_TIME) {
      step = 1;
      lastUpdate = currentMillis;
    }
  } else if (step == 1) { // Yellow
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    if (currentMillis - lastUpdate >= YELLOW_TIME) {
      step = 2;
      lastUpdate = currentMillis;
    }
  } else { // Red
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    if (currentMillis - lastUpdate >= RED_TIME) {
      step = 0;
      lastUpdate = currentMillis;
    }
  }
}
