"""controller_e-puck-python controller."""

from controller import Robot, Motor

TIME_STEP = 64

# Inisialisasi robot
robot = Robot()

# Dapatkan perangkat motor
left_motor = robot.getDevice("left wheel motor")
right_motor = robot.getDevice("right wheel motor")

# Set posisi target motor
left_motor.setPosition(20.0)
right_motor.setPosition(20.0)

# Loop utama
while robot.step(TIME_STEP) != -1:
    pass
