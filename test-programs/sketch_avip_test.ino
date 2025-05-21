
// Constants
const int NO_SIGNAL = 0;
const int STOP = 1;
const int GO_LEFT = 2;
const int GO_RIGHT = 3;
const int GO_FORWARD = 4;
const int AUTONOMOUS_MODE = 5;

// Global variables
int curr_state = NO_SIGNAL, prev_state = NO_SIGNAL;  

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int o2 = digitalRead(2), o3 = digitalRead(3), o4 = digitalRead(4), o5 = digitalRead(5);

  // SET THE CURRENT STATE
  if (o2 == 0 && o3 == 0 && o4 == 0 && o5 == 0) curr_state = NO_SIGNAL; // 0000
  else if (o2 == 0 && o3 == 0 && o4 == 0 && o5 == 1) curr_state = STOP; // 0001
  else if (o2 == 0 && o3 == 0 && o4 == 1 && o5 == 0) curr_state = GO_LEFT; // 0010
  else if (o2 == 0 && o3 == 0 && o4 == 1 && o5 == 1) curr_state = GO_RIGHT; // 0011
  else if (o2 == 0 && o3 == 1 && o4 == 0 && o5 == 0) curr_state = GO_FORWARD; // 0100
  else if (o2 == 0 && o3 == 1 && o4 == 0 && o5 == 1) curr_state = AUTONOMOUS_MODE; // 0101

  // Current state is the same as the previous one
  if (curr_state != prev_state) {

    // Display correct statements to pedestrians
    if (curr_state == NO_SIGNAL) { 
      digitalWrite(LED_BUILTIN, LOW);
    }
    
    else if (curr_state == STOP) {
      // Turn on LED
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);

      // Turn of LED
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
    }

    else if (curr_state == GO_LEFT) {
      // Turn on LED
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);

      // Turn of LED
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
    }

    else if (curr_state == GO_RIGHT) {
      // Turn on LED
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);

      // Turn of LED
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
    }

    else if (curr_state == GO_FORWARD) {
      // Turn on LED
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);

      // Turn of LED
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
    }

    else if (curr_state == AUTONOMOUS_MODE) {
      // Turn on LED
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);

      // Turn of LED
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
    }

    // Save current state as the previous one
    prev_state = curr_state;
  }
}
