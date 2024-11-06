#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define pin_A_mux A1
#define pin_B_mux A2
#define pin_C_mux A3
#define pin_X_mux A7

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

boolean A[8] = {0, 1, 0, 1, 1, 0, 0, 1}; 
boolean B[8] = {0, 0, 1, 1, 0, 0, 1, 1}; 
boolean C[8] = {0, 0, 0, 0, 1, 1, 1, 1};

char buff[100];
int index_menu = 0;
int run_speed = 150;
byte Kp = 0;
byte Ki = 0;
byte Kd = 0;
boolean polMotor_L = 0;
boolean polMotor_R = 0;

#define GARIS_HITAM 0
#define GARIS_PUTIH 1

#define OR 1
#define XOR 2

struct dataSetting {
  int speed;
  byte kp;
  byte ki;
  byte kd;
  unsigned int calibration_value[8];
  char name[15];
};

dataSetting setting;

bool robotRunning = false;

void setup() {
  begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();
  setPID(7, 0, 2);
  polaritasMotor(0, 0);
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

void polaritasMotor(boolean left, boolean right) {
  polMotor_L = left;
  polMotor_R = right;
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

byte readSensor() {
  unsigned int valSensor[8];
  byte dataSensorBit = 0b00000000;
  for (int i = 0; i < 8; i++) {
    digitalWrite(pin_A_mux, A[i]);
    digitalWrite(pin_B_mux, B[i]);
    digitalWrite(pin_C_mux, C[i]);
    delayMicroseconds(20);
    valSensor[i] = analogRead(pin_X_mux);
    if (valSensor[i] > setting.calibration_value[i]) {
      dataSensorBit = dataSensorBit + (0b10000000 >> i);
    }
  }
  return dataSensorBit;
}

void setMotor(int LL, int RR){
  if (RR < 0){
    digitalWrite(pin_dir_motor_R, 1);
    analogWrite(pin_pwm_motor_R, -RR);
  }
  if (RR >= 0){
    digitalWrite(pin_dir_motor_R, 0);
    analogWrite(pin_pwm_motor_R, RR);
  }
  if (LL < 0){
    digitalWrite(pin_dir_motor_L, 1);
    analogWrite(pin_pwm_motor_L, -LL);
  }
  if (LL >= 0){
    digitalWrite(pin_dir_motor_L, 0);
    analogWrite(pin_pwm_motor_L, LL); 
  }
}

double P = 0;
double D = 0;
double I = 0;
double error = 0;
double lastError = 0;
double lastProcess = 0;
double sumOut = 0;

void followLine(byte dataSensor) {
  double current_millis = millis();
  double deltaTime = (current_millis - lastProcess) / 1000;
  switch (dataSensor) {
  case 0b00011000:
    error = 0;
    break;
  case 0b00011100:
    error = -1;
    break;
  case 0b00111000:
    error = 1;
    break;
  case 0b00001000:
    error = -1;
    break;
  case 0b00010000:
    error = 1;
    break;
  case 0b00001100:
    error = -2;
    break;
  case 0b00110000:
    error = 2;
    break;
  case 0b00001110:
    error = -3;
    break;
  case 0b01110000:
    error = 3;
    break;
  case 0b00000100:
    error = -3;
    break;
  case 0b00100000:
    error = 3;
    break;
  case 0b00000110:
    error = -4;
    break;
  case 0b01100000:
    error = 4;
    break;
  case 0b00000010:
    error = -5;
    break;
  case 0b01000000:
    error = 5;
    break;
  case 0b00000011:
    error = -6;
    break;
  case 0b11000000:
    error = 6;
    break;
  case 0b00000001:
    error = -8;
    break;
  case 0b10000000:
    error = 8;
    break;
  }
  Serial.println(error);

  P = error * Kp;
  D = ((error - lastError) * Kd) / deltaTime;
  if (dataSensor & 0b01111110){
    sumOut = 0;
    I = 0;
  } else {
    sumOut += error * deltaTime;
    I = sumOut * Ki;
  }

  double rateError = error - lastError;
  lastError = error;
  double moveVal = P + I + D;
  double moveLeft = run_speed - moveVal;
  double moveRight = run_speed + moveVal;

  if (moveLeft > 255) {
    moveLeft = 255;
  }
  if (moveLeft < -255) {
    moveLeft = -255;
  }
  if (moveRight > 255) {
    moveRight = 255;
  }
  if (moveRight < -255) {
    moveRight = -255;
  }
  setMotor(moveLeft, moveRight);
}

void calibrate_sensor() {
  lcd.clear();
  unsigned int minValue[8] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
  unsigned int maxValue[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  delay(300);

  unsigned long LMC = millis();
  setMotor(-50, 50);
  while (millis() - LMC < 5300) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(pin_A_mux, A[i]);
      digitalWrite(pin_B_mux, B[i]);
      digitalWrite(pin_C_mux, C[i]);
      delayMicroseconds(20);
      if (analogRead(pin_X_mux) > maxValue[i]) {
        maxValue[i] = analogRead(pin_X_mux);
      }
      if (analogRead(pin_X_mux) < minValue[i]) {
        minValue[i] = analogRead(pin_X_mux);
      }
    }
    int sens = readSensor();
    for (int i = 0; i < 8; i++) {
      lcd.setCursor((i+4), 1);
      if ((sens << i) & 0b10000000) {
        lcd.print("I");
      } else {
        lcd.print(".");
      }
    }
    lcd.display();
    
    if (!button_OK) {
      delay(300);
      index_menu = 2;
    }
  }
  setMotor(0, 0);

  for (int i = 0; i < 8; i++) {
    setting.calibration_value[i] = (maxValue[i] + minValue[i]) / 2;
  }
  saveSetting();
}

void begin() {
  Serial.begin(9600);
  pinMode(pin_button_OK, INPUT_PULLUP);
  pinMode(pin_button_DOWNL, INPUT_PULLUP);
  pinMode(pin_button_UPR, INPUT_PULLUP);
  pinMode(pin_button_DOWNR, INPUT_PULLUP);

  pinMode(pin_dir_motor_L, OUTPUT);
  pinMode(pin_pwm_motor_L, OUTPUT);
  pinMode(pin_dir_motor_R, OUTPUT);
  pinMode(pin_pwm_motor_R, OUTPUT);

  pinMode(pin_A_mux, OUTPUT);
  pinMode(pin_B_mux, OUTPUT);
  pinMode(pin_C_mux, OUTPUT);

  lcd.backlight();
  lcd.clear();

  loadSetting();

  calibrate_sensor();
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
      calibrate_sensor();
      break;
    case 2:
      displaySensor();
      break;
    case 3:
      robotRunning = true;
      break;
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
    lcd.print("> Kalibrasi");}
  if(menuIndex == 2){
    lcd.setCursor(0, 1);
    lcd.print("> Display Sensor");}
  if(menuIndex == 3){
    lcd.setCursor(0, 1);
    lcd.print("> Run Robot");}
  delay(250);
}

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

void displaySensor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Read Sensor:");
  while (true) {
    int sens = readSensor();
    for (int i = 0; i < 8; i++) {
      lcd.setCursor((i+4), 1);
      if ((sens << i) & 0b10000000) {
        lcd.print("I");
      } else {
        lcd.print(".");
      }
    }
    if (!button_OK) {
      delay(200);
      break;
    }
  }
}

void RobotLoop() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("RUNNING-");
  while (true) {
    byte sensorValue = readSensor();
    for (int i = 0; i < 8; i++) {
      lcd.setCursor((i+4), 1);
      if ((sensorValue << i) & 0b10000000) {
        lcd.print("I");
      } else {
        lcd.print(".");
      }
    }
    lcd.display();
    followLine(sensorValue);
    if (!button_OK) {
      setMotor(0, 0);
      robotRunning = false;
      delay(200);
      break;
    }
  }
}