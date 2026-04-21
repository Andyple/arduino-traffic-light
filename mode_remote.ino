#include "IRremote.h"

/*
 * mode_remote.ino
 * Logic for controlling the traffic light remotely via an IR sensor.
 */

// Define pin for IR Receiver
const int IR_RECEIVE_PIN = 9; // Changed from 10 to avoid conflict with Sensor Mode

enum LightState { REMOTE_RED, REMOTE_GREEN };
static LightState currentState = REMOTE_RED; // start on red

/*-----( Declare objects )-----*/
static IRrecv irrecv(IR_RECEIVE_PIN);     // create instance of 'irrecv'
// variable used to store the last decodedRawData
static uint32_t last_decodedRawData = 0;

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
{
  // Check if it is a repeat IR code 
  if (irrecv.decodedIRData.flags)
  {
    // set the current decodedRawData to the last decodedRawData 
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    Serial.println("REPEAT!");
  } else
  {
    // output the IR code on the serial monitor
    Serial.print("IR code:0x");
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
  }
  // map the IR code to the remote key
  switch (irrecv.decodedIRData.decodedRawData)
  {
    case 0xBA45FF00: Serial.println("POWER"); break;
    case 0xB847FF00: Serial.println("FUNC/STOP"); // changes the light to red.
       if (currentState == REMOTE_RED){
        Serial.println("Already red, ignoring.");
        break;
       }

       digitalWrite(GREEN_LED, LOW);
       digitalWrite(YELLOW_LED, HIGH);
       delay(5000); // 5 seconds
       digitalWrite(YELLOW_LED, LOW);
       digitalWrite(RED_LED, HIGH);
       currentState = REMOTE_RED;
       break;
    case 0xB946FF00: Serial.println("VOL+"); break;
    case 0xBB44FF00: Serial.println("FAST BACK");    break;
    case 0xBF40FF00: Serial.println("PAUSE");    break;
    case 0xBC43FF00: Serial.println("FAST FORWARD");   break;
    case 0xF807FF00: Serial.println("DOWN");    break;
    case 0xEA15FF00: Serial.println("VOL-");    break;
    case 0xF609FF00: Serial.println("UP");    break;
    case 0xE619FF00: Serial.println("EQ");    break;
    case 0xF20DFF00: Serial.println("ST/REPT"); // changes it to green.
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      currentState = REMOTE_GREEN;
      break;
    case 0xE916FF00: Serial.println("0");    break;
    case 0xF30CFF00: Serial.println("1");    break;
    case 0xE718FF00: Serial.println("2");    break;
    case 0xA15EFF00: Serial.println("3");    break;
    case 0xF708FF00: Serial.println("4");    break;
    case 0xE31CFF00: Serial.println("5");    break;
    case 0xA55AFF00: Serial.println("6");    break;
    case 0xBD42FF00: Serial.println("7");    break;
    case 0xAD52FF00: Serial.println("8");    break;
    case 0xB54AFF00: Serial.println("9");    break;
    default:
      Serial.println(" other button   ");
  }
  // store the last decodedRawData
  last_decodedRawData = irrecv.decodedIRData.decodedRawData;
  delay(500); // Do not get immediate repeat
}

void setupRemoteMode() {
  Serial.println("IR Receiver Button Decode Initialized");
  irrecv.enableIRIn(); // Start the receiver

  // LED pins are already set to OUTPUT in main.ino setup? 
  // Wait, main.ino setup was empty in the read_file output. 
  // I'll make sure they are set here or in main.
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RED_LED, HIGH); // set starting state to red
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  currentState = REMOTE_RED;
}

void runRemoteMode() {
  if (irrecv.decode()) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
}
