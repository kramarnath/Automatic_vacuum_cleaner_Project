/* ------------------------------------------------------------
   AUTOMATIC VACUUM CLEANER ROBOT
   Using Arduino + 3 Ultrasonic Sensors + IR edge detector
   Movement controlled through L298N Motor Driver
-------------------------------------------------------------*/

const int trigPin1 = 3;     // Left sensor trigger
const int echoPin1 = 5;     // Left sensor echo

const int trigPin2 = 6;     // Front sensor trigger
const int echoPin2 = 9;     // Front sensor echo

const int trigPin3 = 10;    // Right sensor trigger
const int echoPin3 = 11;    // Right sensor echo

int irPin = 2;              // IR floor sensor

// Motor driver pins
int motor1A = 4;
int motor1B = 7;
int motor2A = 8;
int motor2B = 12;

// Variables
long duration1, duration2, duration3;
int distLeft, distFront, distRight;

int a = 0;   // floor status memory bit

// -------------------------------------------------------------
// Setup
// -------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);

  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);

  pinMode(irPin, INPUT);

  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
}

// -------------------------------------------------------------
// Function to read distance from ultrasonic sensor
// -------------------------------------------------------------
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// -------------------------------------------------------------
// Motor control functions
// -------------------------------------------------------------
void moveForward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void moveBackward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void turnLeft() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void turnRight() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void stopBot() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}

// -------------------------------------------------------------
// Main Loop
// -------------------------------------------------------------
void loop() {

  // Read all sensor distances
  distLeft  = getDistance(trigPin1, echoPin1);
  distFront = getDistance(trigPin2, echoPin2);
  distRight = getDistance(trigPin3, echoPin3);

  int s = digitalRead(irPin); // IR floor status

  Serial.print("L: "); Serial.print(distLeft);
  Serial.print("  F: "); Serial.print(distFront);
  Serial.print("  R: "); Serial.print(distRight);
  Serial.print("  IR: "); Serial.println(s);

  // If floor missing → move backward once, then force left turn
  if (s == HIGH) {
    moveBackward();
    delay(700);
    a = 1;
  }

  // If safe floor and no memory flag, move forward
  if ((a == 0) && (s == LOW) &&
      distLeft > 15 && distFront > 15 && distRight > 15) {
    moveForward();
  }

  // Right turn condition
  else if ((a == 0) && s == LOW &&
          (distLeft <= 15 && distFront > 15 && distRight <= 15)) {
    turnRight();
  }

  // Left turn (forced or obstacle)
  else if ((a == 1 && s == LOW) ||
           (s == LOW && distLeft <= 15 && distFront <= 15 && distRight > 15)) {
    turnLeft();
    delay(100);
    a = 0;
  }

  // Right-side obstacle → go left
  else if (s == LOW &&
          ((distLeft > 15 && distFront <= 15 && distRight <= 15) ||
           (distLeft > 15 && distFront > 15 && distRight <= 15) ||
           (distLeft > 15 && distFront <= 15 && distRight > 15))) {
    turnLeft();
  }

  delay(50);
}
