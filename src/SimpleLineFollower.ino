// Define Pins
// DC M1 - Right motor
const int INA = 7;
const int INB = 5;
// DC M2 - Left motor
const int INC = 8;
const int IND = 6;

// Define variables
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;

// Define functions
void moveForward();
void turnLeft();
void turnRight();
void stopMoving();

void setup() {
    // Sensors are inputs
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);
    pinMode(sensor4, INPUT);
    
    // Motors are outputs
    pinMode(INA, OUTPUT);
    pinMode(INB, OUTPUT);
    pinMode(INC, OUTPUT);
    pinMode(IND, OUTPUT);
}

void loop() {
    // Read the Sensors. If the value read is > 900 it is on a white surface,
    // if <= 900 it is on a black surface
    sensor1 = analogRead(A0);
    sensor2 = analogRead(A1);
    sensor3 = analogRead(A2);
    sensor4 = analogRead(A3);
    
    if (sensor1 <= 900 && sensor2 <= 900 && sensor3 <= 900 && sensor4 <= 900) {
        // The EEE-Bot should stop moving
        stopMoving();
    } 
    else if (sensor1 <= 900) {
        // The EEE-Bot should turn left
        turnLeft();
        delay(80);
    } 
    else if (sensor4 <= 900) {
        // The EEE-Bot should turn right
        turnRight();
        delay(80);
    } 
    else {
        // The EEE-Bot should move forward
        moveForward();
        delay(80);
    }
}

void moveForward() {
    digitalWrite(INA, LOW);
    analogWrite(INB, 255);
    digitalWrite(INC, LOW);
    analogWrite(IND, 255);
}

void turnLeft() {
    digitalWrite(INA, LOW);
    analogWrite(INB, 255);
    digitalWrite(INC, LOW);
    analogWrite(IND, 130);
}

void turnRight() {
    digitalWrite(INA, LOW);
    analogWrite(INB, 130);
    digitalWrite(INC, LOW);
    analogWrite(IND, 255);
}

void stopMoving() {
    digitalWrite(INA, LOW);
    analogWrite(INB, 0);
    digitalWrite(INC, LOW);
    analogWrite(IND, 0);
}
