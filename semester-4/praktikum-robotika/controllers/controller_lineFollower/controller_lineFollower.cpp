#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

using namespace webots;

int main() {
    Robot robot;
    int time_step = 32;
    double max_speed = 1.28;
    
    // Motor
    Motor *left_motor = robot.getMotor("left wheel motor");
    Motor *right_motor = robot.getMotor("right wheel motor");
    left_motor->setPosition(INFINITY);
    right_motor->setPosition(INFINITY);
    left_motor->setVelocity(0.0);
    right_motor->setVelocity(0.0);
    
    // Enable IR Sensor
    DistanceSensor *left_ir = robot.getDistanceSensor("ir0");
    left_ir->enable(time_step);
    
    DistanceSensor *right_ir = robot.getDistanceSensor("ir1");
    right_ir->enable(time_step);
    
    // Step simulation
    while (robot.step(time_step) != -1) {
        // Read IR Sensor
        double left_ir_value = left_ir->getValue();
        double right_ir_value = right_ir->getValue();
        
        printf("left: %f right: %f\n", left_ir_value, right_ir_value);
            
        double left_speed = max_speed;
        double right_speed = max_speed;
        
        if ((left_ir_value > right_ir_value)) {
            printf("Go left");
            left_speed = -max_speed;
        } else if ((left_ir_value < right_ir_value)) {
            printf("Go right");
            right_speed = -max_speed;
        }

        
        left_motor->setVelocity(left_speed);
        right_motor->setVelocity(right_speed);
    }
    
    return 0;
}
