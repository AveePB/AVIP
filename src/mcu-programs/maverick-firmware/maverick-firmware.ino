#include <Servo.h>

// Packet Constants
const uint8_t HEADER = 0xAA;
const int PACKET_SIZE = 4;

// Servo constants
const int SERVO_PIN = 5, SERVO_L = 2100, SERVO_N = 1500, SERVO_R = 1020;

// ESC constants
const int ESC_PIN = 6, ESC_FWD = 1575, ESC_STOP = 1495, ESC_BWD = 1125;
const int THROTTLE_BRAKING = -1, THROTTLE_FORWARD = 1, THROTTLE_STANDSTILL = 0;

// Timing constants
const int  CMD_DURATION_MS = 500, BRAKE_DURATION_MS = 100;
const long BAUD_RATE = 115200;

// Global variables
Servo esc, servo;
unsigned long lastCmdMillis = 0, brakingMillis = 0;
int prevThrottleCmd = 0;

void setSteering(int steeringRatio);
void setThrottle(int throttleCmd);

void setup() {
  // 1. Setup serial
  Serial.begin(BAUD_RATE);
  while (!Serial) {}

  // 2. Setup servo
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(SERVO_N);

  // 3. Setup ESC
  esc.attach(ESC_PIN);
  esc.writeMicroseconds(ESC_STOP);
}

void loop() {
  // 1. Check for input
   while (Serial.available() >= PACKET_SIZE) {
    uint8_t header = Serial.read();

    if (header == HEADER) {
      int8_t steeringRaw = (int8_t)Serial.read();
      int8_t throttleRaw = (int8_t)Serial.read();
      uint8_t checksum = Serial.read();

      // Verify integrity (XOR check)
      if (checksum == (header ^ (uint8_t)steeringRaw ^ (uint8_t)throttleRaw)) {
        setSteering((int)steeringRaw);
        setThrottle((int)throttleRaw);
        lastCmdMillis = millis();
      }
    }
  }

  // 2. Failsafe
  if (millis() - lastCmdMillis > CMD_DURATION_MS) {
    setSteering(0);
    setThrottle(0);
  }
}

void setSteering(int steeringRatio) {
  steeringRatio = constrain(steeringRatio, -100, 100);
  int pulseWidth;
  
  // I. Turn left
  if (steeringRatio < 0) 
    pulseWidth = map(steeringRatio, -100, 0, SERVO_L, SERVO_N);
  
  // II. Turn right
  else 
    pulseWidth = map(steeringRatio, 0, 100, SERVO_N, SERVO_R);
  servo.writeMicroseconds(pulseWidth);
}

void setThrottle(int throttleCmd) {
  // I. Forward mode
  if (throttleCmd == THROTTLE_FORWARD) {
    esc.writeMicroseconds(ESC_FWD);
    prevThrottleCmd = THROTTLE_FORWARD;
  }

  else {
    switch (prevThrottleCmd) {
      // II. Start braking mode
      case THROTTLE_FORWARD:
        esc.writeMicroseconds(ESC_BWD);
        brakingMillis = millis();
        prevThrottleCmd = THROTTLE_BRAKING;
        break;
      
      // III. Continue braking
      case THROTTLE_BRAKING:
        if (millis() - brakingMillis < BRAKE_DURATION_MS) {  
          esc.writeMicroseconds(ESC_BWD);
        }
        else {
          esc.writeMicroseconds(ESC_STOP);
          prevThrottleCmd = THROTTLE_STANDSTILL;
        }
        break;

      // IV. Standstill mode
      default:
        esc.writeMicroseconds(ESC_STOP);
        prevThrottleCmd = THROTTLE_STANDSTILL;
      break;
    }
  }
}