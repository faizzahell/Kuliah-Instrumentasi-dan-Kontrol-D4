#include <iostream>
#include <cstring>
using namespace std;

int main() {
  float starting_point = 222.46;
  float degree = 227.76;

  float condition_lowLeft_1 = 0;
  float condition_lowLeft_2 = 0;
  float condition_lowLeft_3 = 0;
  float condition_lowLeft_4 = 0;
  float sum_condition_lowleft = 0;
  bool condition_lowleft = false;

  float condition_left_1 = 0;
  float condition_left_2 = 0;
  float condition_left_3 = 0;
  float condition_left_4 = 0;
  float sum_condition_left = 0;
  bool condition_left = false;

  float lambat = 150;
  float cepat = 200;

  float left_motor;
  float right_motor;

  char direction[10];

  /* input */
  float compass_angle = degree - starting_point; // 5.3

  /* proses fuzzifikasi */

  /* analisis keanggotaan sedikit kiri */
  if (compass_angle >= 0 && compass_angle <= 10) {
    condition_lowLeft_1 = 0; // karena telah berada di range x > 0

    if (compass_angle > 0 && compass_angle <= 5) {
      condition_lowLeft_2 = (compass_angle - 0) / (5 - 0); // 0
    }

    if (compass_angle > 5 && compass_angle <= 10) {
      condition_lowLeft_3 = (10 - compass_angle) / (10 - 5); // 0.94
    }

    condition_lowLeft_4 = 0; // karena telah berada di range x < 10

    sum_condition_lowleft = condition_lowLeft_1 + condition_lowLeft_2 + condition_lowLeft_3 + condition_lowLeft_4; // 0.94
  }

  /* analisis keanggotaan kiri */
  if (compass_angle >= 5 && compass_angle <= 15) {
    condition_left_1 = 0; // karena telah berada di range x > 5

    if (compass_angle > 5 && compass_angle <= 10) {
      condition_left_2 = (compass_angle - 5) / (10 - 5); // 0.06
    }

    if (compass_angle > 10 && compass_angle <= 15) {
      condition_left_3 = (15 - compass_angle) / (15 - 10); // 0
    }

    condition_left_4 = 0; // karena telah berada di range x < 15

    sum_condition_left = condition_left_1 + condition_left_2 + condition_left_3 + condition_left_4; // 0.06
  }

  /* proses penerapan rule fuzzy */

  if (sum_condition_lowleft > 0 && sum_condition_lowleft <= 1) {
    condition_lowleft = true;
  } else {
    condition_lowleft = false;
  }

  if (sum_condition_left > 0 && sum_condition_left <= 1) {
    condition_left = true;
  } else {
    condition_left = false;
  }

  /* proses defuzification */

  if (condition_lowleft == true && condition_left == true) {
    left_motor = lambat; // 150 pwm
    right_motor = cepat; // 200 pwm
  }

  if (((sum_condition_lowleft + sum_condition_left) == 1) && ((left_motor - right_motor) < 0)) {
    strcpy(direction, "Kiri");
  }

  /* output */
  cout << direction << endl;
  cout << "Left motor: " << left_motor << endl;
  cout << "Right motor: " << right_motor << endl;

  return 0;
}