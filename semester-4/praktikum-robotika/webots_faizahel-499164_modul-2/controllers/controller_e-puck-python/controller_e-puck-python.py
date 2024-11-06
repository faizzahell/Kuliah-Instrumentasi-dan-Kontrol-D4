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

# Set posisi target motor
left_position_AC = 74.5
right_position_AC = 74.5

left_position_CD = 104.5
right_position_CD = 104.5

left_position_DE = 80.5
right_position_DE = 80.5

left_motor.setVelocity(speed * max_speed)
right_motor.setVelocity(speed * max_speed)

# konfirmasi
move_AC_confirm = False
move_CD_confirm = False

# Function
def turn_left():
    print("Robot belok ke kiri")
    left_motor.setPosition(50)

def rotate():
    print("robot berputar arah")
    left_motor.setPosition(105)
    
    robot.step(8000)

def move_AC():
    global move_AC_confirm
    
    left_motor.setPosition(left_position_AC)
    right_motor.setPosition(right_position_AC)
    
    move_AC_confirm = True
    
def move_CD():
    global move_CD_confirm
    
    print("Robot telah mencapai posisi point C:", left_position_AC, right_position_AC)
    
    left_motor.setPosition(left_position_CD)
    right_motor.setPosition(right_position_CD)
    
    move_CD_confirm = True
    
    robot.step(8000)
    
def move_DE():
    print("Robot telah mencapai posisi point D:", left_position_CD, right_position_CD)
    
    left_motor.setPosition(left_position_DE)
    right_motor.setPosition(right_position_DE)

move_AC()

# Loop utama
while robot.step(TIME_STEP) != -1:
    left_current_position = left_position_sensor.getValue()
    right_current_position = right_position_sensor.getValue()
    
    print(left_current_position)
    print(right_current_position)
    
    if move_AC_confirm == True and left_current_position >= (left_position_AC - tolerance) and right_current_position >= (right_position_AC - tolerance):
        robot.step(1000)
        rotate()
        move_CD()
        move_AC_confirm = False
        
    if move_CD_confirm == True and left_current_position <= (left_position_CD + tolerance) and right_current_position <= (right_position_CD + tolerance):
        robot.step(1000)
        turn_left()
        robot.step(4000)
        move_DE()
        move_CD_confirm = False
        
        print(left_current_position)
