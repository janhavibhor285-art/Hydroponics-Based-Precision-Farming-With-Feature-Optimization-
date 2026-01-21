// L293D Motor Speed and Direction Control with Arduino

// Define the pins connected to the L293D
int enablePin = 5;   // Enable pin (EN) connected to Arduino digital pin 9
int in1Pin = 18;      // Input 1 (IN1) connected to Arduino digital pin 8
int in2Pin = 19;      // Input 2 (IN2) connected to Arduino digital pin 7

void setup() {
  // Define the motor control pins as outputs
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  
  // Initialize the motor to be off (no movement)
  digitalWrite(enablePin, LOW);
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
}

void loop() {
  // Move the motor forward at gradually increasing speed
  motorForward();
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(enablePin, speed);
    delay(10);
  }
  delay(1000); // Wait for 1 second at full speed
  
  // Move the motor backward at gradually increasing speed
  motorBackward();
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(enablePin, speed);
    delay(10);
  }
  delay(1000); // Wait for 1 second at full speed
  
  // Stop the motor
  motorStop();
  delay(1000); // Wait for 1 second at stopped position
}

void motorForward() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
}

void motorBackward() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
}

void motorStop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enablePin, 0); // Set speed to 0 to stop the motor
}
