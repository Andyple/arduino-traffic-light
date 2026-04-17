# Arduino Multi-Mode Traffic Light

A versatile Arduino-based traffic light simulator featuring three distinct operational modes, controlled by hardware push buttons.

## Project Structure

This project uses a modular design within the Arduino IDE. The main sketch handles mode selection via button inputs, while the logic for each traffic light behavior is separated into its own file.

*   `main.ino`: The core controller. Manages setup, button polling, and the state machine that switches between the three modes.
*   `mode_standard.ino`: Simulates a standard timed traffic light cycle (Green -> Yellow -> Red).
*   `mode_sensor.ino`: Uses an ultrasonic sensor to detect approaching vehicles and trigger light changes.
*   `mode_remote.ino`: Allows manual control of the traffic light sequence using an IR remote.

## Hardware Requirements

*   1x Arduino Board (e.g., Uno, Nano)
*   3x LEDs (Red, Yellow, Green)
*   3x Push Buttons for mode selection
*   1x HC-SR04 Ultrasonic Distance Sensor
*   1x IR Receiver Module
*   1x IR Remote Control

## How it Works

1.  Upon powering on, the system defaults to Standard Mode.
2.  Pressing Button 1 activates Standard Mode.
3.  Pressing Button 2 activates Sensor Mode.
4.  Pressing Button 3 activates Remote Mode.
5.  Only one mode is active at any given time. The `main.ino` loop continuously polls the buttons and delegates execution to the selected mode.
