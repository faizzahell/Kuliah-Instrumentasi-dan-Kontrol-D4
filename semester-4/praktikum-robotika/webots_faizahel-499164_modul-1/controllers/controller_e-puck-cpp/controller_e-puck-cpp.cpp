// File:          controller_e-puck-cpp.cpp
// Date:
// Description:
// Author:
// Modifications:

// Bergerak lurus (posisi)

#include <webots/Robot.hpp>
#include <webots/Motor.hpp>

#define TIME_STEP 64

int main() {
  // Inisialisasi robot
  webots::Robot robot;

  // Dapatkan perangkat motor
  webots::Motor left_motor = *robot.getMotor("left wheel motor");
  webots::Motor right_motor = *robot.getMotor("right wheel motor");

  // Set posisi target motor
  left_motor.setPosition(20.0);
  right_motor.setPosition(20.0);

  // Loop utama
  while (robot.step(TIME_STEP) != -1);

  return 0;
}
