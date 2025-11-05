/*
  PROJECT: AI-Powered Prosthetic Limb - PART 1: DATA COLLECTION
  
  PURPOSE:
  This code reads all sensors (FSR, Accel, etc.) and controls the servos
  using a SIMPLE 'map()' function.
  
  Its MOST IMPORTANT job is to print all this data to the Serial Monitor
  in CSV format. You will copy this data to train your AI model.
  
  Libraries to install:
  - Adafruit SSD1366
  - Adafruit GFX Library
  - Adafruit ADXL345
  - Adafruit BusIO
  - Adafruit Unified Sensor
  - Adafruit PWM Servo Driver Library
  - Blynk
*/

// --- BLYNK CONFIGURATION ---
#define BLYNK_TEMPLATE_ID "TMPL3DZyCh99j"
#define BLYNK_TEMPLATE_NAME "new"
#define BLYNK_AUTH_TOKEN "m9HY-VvKVE3yfa3kqXaaVY20Jk1hVtg0"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "m9HY-VvKVE3yfa3kqXaaVY20Jk1hVtg0";
char ssid[] = "Nothing Phone (2a)_5222";
char pass[] = "100200300";

// --- I2C & COMPONENT LIBRARIES ---
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_PWMServoDriver.h>

// --- PIN DEFINITIONS ---
#define I2C_SDA 21
#define I2C_SCL 22
#define FSR1_PIN 34
#define FSR2_PIN 35
#define TRIG_PIN 12
#define ECHO_PIN 14
#define VIB_SENSOR_PIN 27
#define VIB_MOTOR_PIN 26

// --- OLED DISPLAY SETUP ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- ACCELEROMETER SETUP ---
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// --- SERVO DRIVER SETUP ---
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVO_FREQ 50
#define SERVOMIN 150
#define SERVOMAX 600

// --- GLOBAL VARIABLES ---
int fsr1_val = 0;
int fsr2_val = 0;
int grip_pressure_avg = 0;
float accelX = 0.0, accelY = 0.0, accelZ = 0.0;
long distance_cm = 0;
int vibration_state = 0;
String motion_direction = "Static";

// --- GRAPHING VARIABLES ---
#define GRAPH_WIDTH 128
#define GRAPH_HEIGHT 30
int gripHistory[GRAPH_WIDTH];
int graph_bottom_y = SCREEN_HEIGHT - 1;

void setup() {
  Serial.begin(115200);
  Serial.println("Prosthetic Hand System: DATA COLLECTION MODE");

  Wire.begin(I2C_SDA, I2C_SCL);

  // --- Initialize OLED Display ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("OLED Init: OK");
  display.display();
  delay(1000);

  // --- Initialize Accelerometer ---
  if (!accel.begin()) {
    Serial.println("Could not find ADXL345 sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("ADXL345 Init: FAIL");
    display.display();
    while (1) delay(10);
  }
  accel.setRange(ADXL345_RANGE_4_G);
  Serial.println("ADXL345 Init: OK");

  // --- Initialize Servo Driver ---
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  Serial.println("PCA9685 Init: OK");

  // --- Initialize Other GPIO Pins ---
  pinMode(FSR1_PIN, INPUT);
  pinMode(FSR2_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(VIB_SENSOR_PIN, INPUT_PULLUP);
  pinMode(VIB_MOTOR_PIN, OUTPUT);
  digitalWrite(VIB_MOTOR_PIN, LOW);

  // --- Initialize Graph History ---
  for (int i = 0; i < GRAPH_WIDTH; i++) {
    gripHistory[i] = 0;
  }

  // --- Connect to WiFi and Blynk ---
  Serial.println("Connecting to WiFi and Blynk...");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();
  Blynk.begin(auth, ssid, pass);
  Serial.println("Blynk Connected!");

  // --- Print CSV Header for Data Logging ---
  Serial.println("\n--- STARTING DATA LOG (Copy from here!) ---");
  Serial.println("fsr1,fsr2,grip_avg,accelX,accelY,accelZ,distance,vibration,servo_pos");
  
  delay(1000);
}

void loop() {
  Blynk.run();
  
  readSensors();
  updateServos_Simple(); // Use the SIMPLE map() function
  updateOLED();
  logDataToSerial();   // Log data for AI
  checkVibration();
  sendDataToBlynk();
  
  delay(50); 
}

void readSensors() {
  // 1. Read FSR Sensors
  fsr1_val = analogRead(FSR1_PIN);
  fsr2_val = analogRead(FSR2_PIN);
  grip_pressure_avg = (fsr1_val + fsr2_val) / 2;

  // 2. Read Accelerometer
  sensors_event_t event;
  accel.getEvent(&event);
  accelX = event.acceleration.x;
  accelY = event.acceleration.y;
  accelZ = event.acceleration.z;
  
  // 3. Determine Motion Direction
  if (accelX > 7.0) motion_direction = "Right";
  else if (accelX < -7.0) motion_direction = "Left";
  else if (accelY > 7.0) motion_direction = "Up";
  else if (accelY < -7.0) motion_direction = "Down";
  else if (abs(accelX) < 2.0 && abs(accelY) < 2.0 && accelZ > 8.0) motion_direction = "Static";

  // 4. Read Ultrasonic Sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  distance_cm = duration * 0.034 / 2;

  // 5. Read Vibration Sensor
  vibration_state = digitalRead(VIB_SENSOR_PIN);
}

void updateServos_Simple() {
  // This is the SIMPLE, NON-AI control logic.
  // It maps the average grip pressure to a servo position.
  // We log this position so the AI can learn this relationship.
  
  int servo_pulse = map(grip_pressure_avg, 0, 4095, SERVOMIN, SERVOMAX);
  servo_pulse = constrain(servo_pulse, SERVOMIN, SERVOMAX);

  // Set all 4 servos to the same position
  for (int s = 0; s < 4; s++) {
    pwm.setPWM(s, 0, servo_pulse);
  }
}

void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.print("Dir: ");
  display.println(motion_direction);

  display.setCursor(0, 9);
  display.print("Grip: ");
  display.print(grip_pressure_avg);
  
  display.setCursor(64, 9);
  display.print("Dist: ");
  display.print(distance_cm);
  display.println("cm");

  display.setCursor(0, 18);
  display.print("A_X: ");
  display.print(accelX);
  
  display.setCursor(0, 27);
  display.print("A_Y: ");
  display.print(accelY);

  drawGraph();
  display.display();
}

void drawGraph() {
  for (int i = 0; i < GRAPH_WIDTH - 1; i++) {
    gripHistory[i] = gripHistory[i + 1];
  }
  int mapped_grip = map(grip_pressure_avg, 0, 4095, 0, GRAPH_HEIGHT);
  gripHistory[GRAPH_WIDTH - 1] = constrain(mapped_grip, 0, GRAPH_HEIGHT);
  
  for (int x = 0; x < GRAPH_WIDTH; x++) {
    display.drawFastVLine(x, graph_bottom_y - gripHistory[x], gripHistory[x], SSD1306_WHITE);
  }
  display.drawFastHLine(0, graph_bottom_y, GRAPH_WIDTH, SSD1306_WHITE);
}

void logDataToSerial() {
  // This function prints all the sensor and actuator data
  // in CSV format for the Python script to read.
  
  Serial.print(fsr1_val);
  Serial.print(",");
  Serial.print(fsr2_val);
  Serial.print(",");
  Serial.print(grip_pressure_avg);
  Serial.print(",");
  Serial.print(accelX);
  Serial.print(",");
  Serial.print(accelY);
  Serial.print(",");
  Serial.print(accelZ);
  Serial.print(",");
  Serial.print(distance_cm);
  Serial.print(",");
  Serial.print(vibration_state == LOW ? 1 : 0);
  Serial.print(",");
  
  // Log the servo position we *sent*
  int current_servo_pulse = map(grip_pressure_avg, 0, 4095, SERVOMIN, SERVOMAX);
  current_servo_pulse = constrain(current_servo_pulse, SERVOMIN, SERVOMAX);
  Serial.println(current_servo_pulse);
}

void checkVibration() {
  digitalWrite(VIB_MOTOR_PIN, (vibration_state == LOW) ? HIGH : LOW);
}

void sendDataToBlynk() {
  Blynk.virtualWrite(V0, grip_pressure_avg);
  Blynk.virtualWrite(V1, distance_cm);
  Blynk.virtualWrite(V2, accelX);
  Blynk.virtualWrite(V3, accelY);
  Blynk.virtualWrite(V4, accelZ);
  Blynk.virtualWrite(V5, motion_direction);
}
