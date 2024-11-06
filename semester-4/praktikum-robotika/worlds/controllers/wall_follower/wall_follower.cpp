#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
#include <vector>

using namespace webots;
using namespace std;

void run_robot(Robot *robot) {
  int timestep = (int)robot->getBasicTimeStep();
  const double max_speed = 6.28;

  // Pastikan nama motor sesuai dengan yang ada di konfigurasi robot
  Motor *left_motor = robot->getMotor("left wheel motor");
  Motor *right_motor = robot->getMotor("right wheel motor");

  // Jika motor tidak ditemukan, keluarkan pesan kesalahan
  if (left_motor == nullptr) {
    cerr << "Error: 'left wheel motor' device not found." << endl;
    return;
  }
  if (right_motor == nullptr) {
    cerr << "Error: 'right wheel motor' device not found." << endl;
    return;
  }

  left_motor->setPosition(INFINITY);
  left_motor->setVelocity(0.0);

  right_motor->setPosition(INFINITY);
  right_motor->setVelocity(0.0);

  vector<DistanceSensor*> prox_sensors(8);
  for (int ind = 0; ind < 8; ++ind) {
    string sensor_name = "ps" + to_string(ind);
    prox_sensors[ind] = robot->getDistanceSensor(sensor_name);
    if (prox_sensors[ind] == nullptr) {
      cerr << "Error: '" << sensor_name << "' device not found." << endl;
      return;
    }
    prox_sensors[ind]->enable(timestep);
  }

  while (robot->step(timestep) != -1) {
    for (int ind = 0; ind < 8; ++ind) {
      cout << "ind: " << ind << ", val: " << prox_sensors[ind]->getValue() << endl;
    }

    bool left_wall = prox_sensors[5]->getValue() > 80;
    bool left_corner = prox_sensors[6]->getValue() > 80;
    bool front_wall = prox_sensors[7]->getValue() > 80;

    double left_speed = max_speed;
    double right_speed = max_speed;

    if (front_wall) {
      cout << "turn right in place" << endl;
      left_speed = max_speed;
      right_speed = -max_speed;
    } else {
      if (left_wall) {
        cout << "drive forward" << endl;
        left_speed = max_speed;
        right_speed = max_speed;
      } else {
        cout << "turn left" << endl;
        left_speed = max_speed / 4;
        right_speed = max_speed;
      }

      if (left_corner) {
        cout << "come to close, drive right" << endl;
        left_speed = max_speed;
        right_speed = max_speed / 8;
      }
    }

    left_motor->setVelocity(left_speed);
    right_motor->setVelocity(right_speed);
  }
}

int main() {
  Robot *my_robot = new Robot();
  run_robot(my_robot);
  delete my_robot;
  return 0;
}
