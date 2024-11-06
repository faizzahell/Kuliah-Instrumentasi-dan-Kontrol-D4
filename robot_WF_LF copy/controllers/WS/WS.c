#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#define TIME_STEP 64
#define THRESHOLD 150 // Threshold for front sensor to detect obstacle

// PID constants
#define kp 1
#define ki 0.007
#define kd 0.0003

double TARGET_DISTANCE = 1000;
double error = 0.0;
double last_error = 0.0;
double derivative = 0.0;
double integral = 0.0;
double pwm = 25;
double output = 0.0;
double left_speed = 0.0;
double right_speed = 0.0;

int main(int argc, char **argv) {
  wb_robot_init();
  
  WbDeviceTag WSKiri = wb_robot_get_device("WS-Kiri");
  wb_distance_sensor_enable(WSKiri, TIME_STEP);
  WbDeviceTag WSDepan = wb_robot_get_device("WS-Depan");
  wb_distance_sensor_enable(WSDepan, TIME_STEP);
  WbDeviceTag WSKanan = wb_robot_get_device("WS-Kanan");
  wb_distance_sensor_enable(WSKanan, TIME_STEP);
  
  WbDeviceTag Kiri = wb_robot_get_device("RodaKiri");
  WbDeviceTag Kanan = wb_robot_get_device("RodaKanan");
  
  wb_motor_set_position(Kiri, INFINITY);
  wb_motor_set_position(Kanan, INFINITY);
  
  while (wb_robot_step(TIME_STEP) != -1) {
    double val1 = wb_distance_sensor_get_value(WSKiri);
    double val2 = wb_distance_sensor_get_value(WSDepan);
    double val3 = wb_distance_sensor_get_value(WSKanan);
    
    printf("sensor Left = %.0f ", val1);
    printf("sensor WS-Depan = %.0f ", val2);
    printf("sensor Right = %.0f \n", val3);

    if (val2 >= THRESHOLD) {
      // If the front sensor does not detect an obstacle, move straight
      left_speed = pwm;
      right_speed = pwm;
    } else {
      // PID calculations to maintain target distance
      error = TARGET_DISTANCE - (val1 + val2 + val3) / 3.0; // Calculate error
      integral += error;
      derivative = error - last_error;
      output = (kp * error) + (ki * integral) + (kd * derivative);
      left_speed = pwm - output;
      right_speed = pwm + output;
   
      if (left_speed > pwm) left_speed = pwm;
      if (right_speed > pwm) right_speed = pwm;
    }
    
    wb_motor_set_velocity(Kiri, left_speed);
    wb_motor_set_velocity(Kanan, right_speed);
    
    last_error = error;
  }

  wb_robot_cleanup();

  return 0;
}
