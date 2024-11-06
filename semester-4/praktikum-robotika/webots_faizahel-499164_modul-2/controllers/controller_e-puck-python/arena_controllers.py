from controller import Robot, Motor

TIME_STEP = 64

# Inisialisasi robot
robot = Robot()

# Dapatkan perangkat motor dan sensor posisi
left_motor = robot.getDevice("left wheel motor")
right_motor = robot.getDevice("right wheel motor")
left_position_sensor = left_motor.getPositionSensor()
right_position_sensor = right_motor.getPositionSensor()

# Aktifkan sensor posisi
left_position_sensor.enable(TIME_STEP)
right_position_sensor.enable(TIME_STEP)

# konstant
max_speed = 6.28

# More settings
tolerance = 0.1
speed = 1

left_motor.setPosition(float('inf'))
right_motor.setPosition(float('inf'))

robot.step(5000)

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

# Loop utama
while robot.step(TIME_STEP) != -1:
    left_current_position = left_position_sensor.getValue()
    right_current_position = right_position_sensor.getValue()
    
    
    
