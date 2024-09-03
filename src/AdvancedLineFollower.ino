/// Define Pins
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
int WA;
int error;

// Define functions
void moveForward();
void turnLeft();
void turnRight();
void stopMoving();
int calculateWeightedAverage(int s1, int s2, int s3, int s4);
int set_motors(int right, int left);

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
    
    Serial.begin(9600);
}

void loop() {
    // Read the Sensors. If the value read is > 4 it is on a white surface
    // if <= 4 it is on a black surface
    sensor1 = analogRead(A0);
    sensor2 = analogRead(A1);
    sensor3 = analogRead(A2);
    sensor4 = analogRead(A3);

    if (sensor1 <= 300 && sensor2 <= 300 && sensor3 <= 300 && sensor4 <= 300) {
        // The EEE-Bot should stop moving
        stopMoving();
    } 
    else if (sensor1 <= 300) {
        // The EEE-Bot should turn left
        turnLeft();
        delay(80);
    } 
    else if (sensor4 <= 300) {
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

int calculateWeightedAverage(int s1, int s2, int s3, int s4) {
    int weightedAverage;
    int weightOfs1 = 0;
    int weightOfs2 = 15;
    int weightOfs3 = 30;
    int weightOfs4 = 45;
    int sumOfWeights;
    int weightedValue;
    
    sumOfWeights = (weightOfs1 + weightOfs2 + weightOfs3 + weightOfs4);
    weightedValue = ((weightOfs1 * s1) + (weightOfs2 * s2) + (weightOfs3 * s3) + (weightOfs4 * s4));
    weightedAverage = (weightedValue / sumOfWeights);
    
    return weightedAverage;
}

void PID() {
    int i; // Control function
    int power_difference = 0;
    float Kp, Ki, Kd;
    int position;
    int derivative, proportional;
    int speed_of_bot = 255;
    int last_proportional = 0;
    int integral = 0;

    while (1) {
        position = calculateWeightedAverage(sensor1, sensor2, sensor3, sensor4);
        Serial.println(position);
        proportional = ((int)position - 3000);

        derivative = proportional - last_proportional;
        integral = integral + proportional;
        last_proportional = proportional;

        // Use the tutorial to set initial values of Kp, Ki, and Kd
        Kp = 30;
        Ki = 0.5;
        Kd = 2;
        power_difference = proportional * Kp + integral * Ki + derivative * Kd;

        const int max = speed_of_bot / 2 + 30;
        if (power_difference > max) power_difference = max;
        if (power_difference < -max) power_difference = (-1 * max);

        if (power_difference < 0) // left
            set_motors(max + power_difference, max);
        else // right
            set_motors(max, max - power_difference);
    }
}

int set_motors(int right, int left) {
    if (sensor1 <= 900 && sensor2 <= 900 && sensor3 <= 900 && sensor4 <= 900) {
        // The EEE-Bot should stop moving
        stopMoving();
    } 
    else if (sensor1 <= 900) {
        // The EEE-Bot should turn left
        digitalWrite(INA, LOW);
        analogWrite(INB, right);
        digitalWrite(INC, LOW);
        analogWrite(IND, left);
    } 
    else if (sensor4 <= 900) {
        // The EEE-Bot should turn right
        digitalWrite(INA, LOW);
        analogWrite(INB, right);
        digitalWrite(INC, LOW);
        analogWrite(IND, left);
    } 
    else {
        // The EEE-Bot should move forward
        digitalWrite(INA, LOW);
        analogWrite(INB, right);
        digitalWrite(INC, LOW);
        analogWrite(IND, left);
    }
}
