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

# ke AC

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(12000)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik C")

robot.step(1000)

# ke CD

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(1450)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(6000)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik D")

robot.step(1000)

# ke DE

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(2540)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik E")

robot.step(1000)

# ke EF

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(1330)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(5800)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(3950)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik F")

robot.step(1000)

# ke FG

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(1450)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(3800)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(701)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(5650)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik G")

robot.step(1000)

# ke GH

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(3880)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik H")

robot.step(1000)

# ke HI

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(1450)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(3880)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik I")

robot.step(1000)

# ke IJ

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(5800)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(7850)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik J")

robot.step(1000)

# ke JK

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(12000)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik K")

robot.step(1000)

# ke KJ

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(1450)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(12000)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik J")

robot.step(1000)

# Ke JB

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(7850)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(5800)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

robot.step(500)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(3870)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik B")

robot.step(1000)

# ke BA

left_motor.setVelocity(-3)
right_motor.setVelocity(3)

robot.step(710)

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

robot.step(5800)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot telah sampai pada titik A")

robot.step(1000)

# Robot Berputar

left_motor.setVelocity(3)
right_motor.setVelocity(-3)

robot.step(1450)

left_motor.setVelocity(0)
right_motor.setVelocity(0)

print("Robot berada di posisi awal")

robot.step(1000)

# Loop utama
while robot.step(TIME_STEP) != -1:
    left_current_position = left_position_sensor.getValue()
    right_current_position = right_position_sensor.getValue()
    
