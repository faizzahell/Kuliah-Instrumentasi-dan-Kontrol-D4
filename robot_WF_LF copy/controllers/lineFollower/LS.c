#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#define TIME_STEP 64
#define THRESHOLD 1000

// PID constants
#define Kp 20.0
#define Ki 0.03
#define Kd 6.0



int main(int argc, char **argv) {
  wb_robot_init();
  
  // Get motor devices
  WbDeviceTag Kiri = wb_robot_get_device("RodaKiri");
  WbDeviceTag Kanan = wb_robot_get_device("RodaKanan");
  
  // Set motors to velocity control mode
  wb_motor_set_position(Kiri, INFINITY);
  wb_motor_set_position(Kanan, INFINITY);
  
  // Get and enable distance sensors
  WbDeviceTag IR[8];
  char sensor_names[8][8] = {"L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8"};
  for (int i = 0; i < 8; i++) {
    IR[i] = wb_robot_get_device(sensor_names[i]);
    wb_distance_sensor_enable(IR[i], TIME_STEP);
  }
  
  // PID variables
  double last_error = 0.0;
  double integral = 0.0;
  double lastProcess = wb_robot_get_time();

  while (wb_robot_step(TIME_STEP) != -1) {
    int sensor_values[8];
    for (int i = 0; i < 8; i++) {
      sensor_values[i] = wb_distance_sensor_get_value(IR[i]);
    }

    // Print raw sensor values before thresholding for debugging
    printf("Raw Sensor Values: ");
    for (int i = 0; i < 8; i++) {
      printf("%d: %d ", i + 1, sensor_values[i]);
    }
    printf("\n");

    // Convert sensor values to binary (0 or 1) based on the threshold
    int binary_sensor_values[8];
    for (int i = 0; i < 8; i++) {
      binary_sensor_values[i] = sensor_values[i] == THRESHOLD ? 1 : 0; // Following black line
    }

    // Print binary sensor values for debugging
    printf("Binary Sensor Values: ");
    for (int i = 0; i < 8; i++) {
      printf("%d: %d ", i + 1, binary_sensor_values[i]);
    }
    printf("\n");

    // Convert binary sensor array to a single byte
    unsigned char binaryValue = 0;
    for (int i = 0; i < 8; i++) {
      binaryValue |= (binary_sensor_values[i] << (7 - i));
    }

    // Determine the error based on binary sensor value
    double error = 0;
    switch (binaryValue) {
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
      default:
        error = 0; // Default error
        break;
    }

    // Calculate PID
    double current_time = wb_robot_get_time();
    double deltaTime = current_time - lastProcess;
    lastProcess = current_time;

    double P = error * Kp;
    integral += error * deltaTime;
    double I = integral * Ki;
    double D = ((error - last_error) / deltaTime) * Kd;

    double moveVal = P + I + D;
    last_error = error;

    // Calculate motor speeds
    double base_speed = 15.0;
    double left_speed = base_speed - moveVal;
    double right_speed = base_speed + moveVal;

    // Limit motor speeds to 0-255 range
    if (left_speed > 255) left_speed = 255;
    if (left_speed < 0) left_speed = 0;
    if (right_speed > 255) right_speed = 255;
    if (right_speed < 0) right_speed = 0;

    // Print PID values for debugging
    printf("Error: %.2f, Correction: %.2f, Left Speed: %.2f, Right Speed: %.2f\n", error, moveVal, left_speed, right_speed);

    wb_motor_set_velocity(Kiri, left_speed);
    wb_motor_set_velocity(Kanan, right_speed);
  };

  wb_robot_cleanup();

  return 0;
}