# Controller of Robot Line Follower

from controller import Robot

def run_robot(ROBOT):
    time_step = 32
    max_speed = 6.28
    
    # Motor
    left_motor = robot.getMotor('left wheel motor')
    right_motor = robot.getMotor('right wheel motor')
    left_motor.setPosition(float('inf'))
    right_motor.setPosition(float('inf'))
    left_motor.setVelocity(0.0)
    right_motor.setVelocity(0.0)
    
    #Enable IR Sensor
    left_ir = robot.getDistanceSensor('ir0')
    left_ir.enable(time_step)
    
    right_ir = robot.getDistanceSensor('ir1')
    right_ir.enable(time_step)
    
    #step simulation
    while robot.setp(time_step) != -1:
        #Read ir Sensor
        left_ir_value = left_ir.getValue()
        right_ir_value = right_ir.getValue()
        
        print("left: {} right: {}".format(left_ir_value, right_ir_value))
            
        left_speed = max_speed
        right_speed = max_speed
        
        left_motor.setVelocity(left_speed)
        right_motor.setVelocity(right_speed)

if __name__ == "__main__":
    my_robot = Robot()
    run_robot(my_robot)            