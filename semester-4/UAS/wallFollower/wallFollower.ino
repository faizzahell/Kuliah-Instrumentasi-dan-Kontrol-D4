#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define pin_dir_motor_L 9
#define pin_pwm_motor_L 5
#define pin_dir_motor_R 10
#define pin_pwm_motor_R 6

#define pin_button_OK A0
#define pin_button_DOWNL 8
#define pin_button_UPR 11
#define pin_button_DOWNR 12

#define button_OK digitalRead(pin_button_OK)
#define button_DOWNL digitalRead(pin_button_DOWNL)
#define button_UPR digitalRead(pin_button_UPR)
#define button_DOWNR digitalRead(pin_button_DOWNR)

#define pin_trigger 7
#define pin_echo_L 2
#define pin_echo_C 3
#define pin_echo_R 4

double distance1, duration1;
double distance2, duration2;
double distance3, duration3;

int index_menu = 0;
int run_speed = 150;
byte Kp = 0;
byte Ki = 0;
byte Kd = 0;

struct dataSetting {
  int speed;
  byte kp;
  byte ki;
  byte kd;
};
dataSetting setting;

bool robotRunning = false;
bool follow_left = false;

double P = 0;
double D = 0;
double I = 0;
double error = 0;
double lastError = 0;
double sumOut = 0;

void setup() {
  begin();
}

void loop() {
  if (robotRunning) {
    RobotLoop();
  } else {
    navigateMenu();
  }
}

void saveSetting() {
  EEPROM.put(0, setting);
}

void loadSetting() {
  EEPROM.get(0, setting);
  run_speed = setting.speed;
  Kp = setting.kp;
  Ki = setting.ki;
  Kd = setting.kd;
}

void setPID(byte p, byte i, byte d) {
  Kp = p;
  Ki = i;
  Kd = d;
  setting.kp = p;
  setting.ki = i;
  setting.kd = d;
  saveSetting();
}

void begin() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();
  setPID(6, 0.1, 1.2);

  pinMode(pin_button_OK, INPUT_PULLUP);
  pinMode(pin_button_DOWNL, INPUT_PULLUP);
  pinMode(pin_button_UPR, INPUT_PULLUP);
  pinMode(pin_button_DOWNR, INPUT_PULLUP);

  pinMode(pin_dir_motor_L, OUTPUT);
  pinMode(pin_pwm_motor_L, OUTPUT);
  pinMode(pin_dir_motor_R, OUTPUT);
  pinMode(pin_pwm_motor_R, OUTPUT);

  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_echo_L, INPUT);
  pinMode(pin_echo_C, INPUT);
  pinMode(pin_echo_R, INPUT);

  lcd.backlight();
  lcd.clear();

  loadSetting();
}

void navigateMenu() {
  static int menuIndex = 0;
  if (!button_UPR) {
    menuIndex++;
    delay(200);
  }
  if (!button_DOWNL) {
    menuIndex--;
    delay(200);
  }
  if (menuIndex < 0) {
    menuIndex = 3;
  }
  if (menuIndex > 3) {
    menuIndex = 0;
  }

  if (!button_OK) {
    delay(200);
    switch (menuIndex) {
    case 0:
      run_speed = setSpeed();
      break;
    case 1:
      robotRunning = true;
      break;
    case 2:
      displaySensor();
      break;
    case 3:
      choice();
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu:");
  if(menuIndex == 0){
    lcd.setCursor(0, 1);
    lcd.print("> Speed");}
  if(menuIndex == 1){
    lcd.setCursor(0, 1);
    lcd.print("> Run Robot");}
  if(menuIndex == 2){
    lcd.setCursor(0, 1);
    lcd.print("> Display Sensor");}
  if(menuIndex == 3){
    lcd.setCursor(0, 1);
    lcd.print("> Select Mode");}
  delay(250);
}

void choice(){
  while(true){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Mode:");
  if (follow_left == true){
    lcd.setCursor(0, 1);
    lcd.print("Follow Left");
    delay(200);
  }
  if (follow_left == false){
    lcd.setCursor(0, 1);
    lcd.print("Follow Right");
    delay(200);
  }
  if (!button_UPR){
    follow_left = true;
    delay(200);
  }
  if (!button_DOWNL){
    follow_left = false;
    delay(200);
  }
  lcd.display();
  if (!button_OK) {
    delay(200);
    return;
    }}}

int setSpeed() {
  int speed = run_speed;
  while (true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed:");
    lcd.setCursor(0, 1);
    lcd.print("Speed: ");
    lcd.setCursor(7, 1);
    lcd.print(speed);
    lcd.display();
    if (!button_UPR) {
      speed += 10;
      if (speed > 255) {
        speed = 255;
      }
      delay(200);
    }
    if (!button_DOWNL) {
      speed -= 10;
      if (speed < 0) {
        speed = 0;
      }
      delay(200);
    }
    if (!button_OK) {
      delay(200);
      setting.speed = speed;
      saveSetting();
      return speed;
    }
  }
}

void setMotor(int LL, int RR) {
  if (RR < 0) {
    digitalWrite(pin_dir_motor_R, 1);
    analogWrite(pin_pwm_motor_R, -RR);
  } else {
    digitalWrite(pin_dir_motor_R, 0);
    analogWrite(pin_pwm_motor_R, RR);
  }
  if (LL < 0) {
    digitalWrite(pin_dir_motor_L, 1);
    analogWrite(pin_pwm_motor_L, -LL);
  } else {
    digitalWrite(pin_dir_motor_L, 0);
    analogWrite(pin_pwm_motor_L, LL);
  }
}

double readUltrasonic1() {
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);
  duration1 = pulseIn(pin_echo_L, HIGH);
  distance1 = duration1 * 0.034 / 2;
  delay(12);
}
double readUltrasonic2() {
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);
  duration2 = pulseIn(pin_echo_C, HIGH);
  distance2 = duration2 * 0.034 / 2;
  delay(12);
}
double readUltrasonic3() {
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trigger, LOW);
  duration3 = pulseIn(pin_echo_R, HIGH);
  distance3 = duration3 * 0.034 / 2;
  delay(12);
}

double lastProcess = 0;

double targetDistance = 15.0; 
const int threshold_distance = 25; 
const int turn_speed = 120;
const int turn_duration = 200; 

void followWall() {
  readUltrasonic1();
  readUltrasonic2();
  readUltrasonic3();
  double distance_L = distance1;
  double distance_C = distance2;
  double distance_R = distance3;

  if (distance_C < threshold_distance) {
    if (follow_left == true) {
      setMotor(turn_speed, 0); 
    } else {
      setMotor(0, turn_speed);
    }
    delay(turn_duration); 
  } else {
    double error;
    if (follow_left == true) {
      error = targetDistance - distance_L;
    } else {
      error = targetDistance - distance_R;
    }
    double currentTime = millis();
    double deltaTime = (currentTime - lastProcess) / 1000.0;

    double P = error * Kp;
    double D = ((error - lastError) * Kd) / deltaTime;
    sumOut += error * deltaTime;
    double I = sumOut * Ki;

    double PIDValue = P + I + D;

    double leftSpeed, rightSpeed;
    if (follow_left == true) {
      leftSpeed = run_speed + PIDValue;
      rightSpeed = run_speed - PIDValue;
    } else {
      leftSpeed = run_speed - PIDValue;
      rightSpeed = run_speed + PIDValue;
    }

    if (leftSpeed > 255) leftSpeed = 255;
    if (leftSpeed < -255) leftSpeed = -255;
    if (rightSpeed > 255) rightSpeed = 255;
    if (rightSpeed < -255) rightSpeed = -255;

    setMotor(leftSpeed, rightSpeed);

    lastError = error;
    lastProcess = currentTime;
  }
}

void RobotLoop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ROBOTO WALL FOLL"));
  lcd.setCursor(0, 1);
  lcd.print(F("---- RUNNING ---"));

  loadSetting();
  followWall();

  if (!button_OK) {
    robotRunning = false;
    setMotor(0, 0);
    delay(200);
  }
}

void displaySensor() {
  while (true) {
    readUltrasonic1();
    readUltrasonic2();
    readUltrasonic3();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Readings:");
    lcd.setCursor(0, 1);
    lcd.print(distance1);
    lcd.setCursor(5, 1);
    lcd.print(distance2);
    lcd.setCursor(10, 1);
    lcd.print(distance3);
    delay(100);

    if (!button_OK) {
      delay(200);
      return;
    }
  }
}