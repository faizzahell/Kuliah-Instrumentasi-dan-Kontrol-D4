"""controller_simulation controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor

from controller import Robot, Camera, Motor

# Konstanta untuk pengolahan citra
WHITE_THRESHOLD = 100

def process_image(camera):
    # Ambil citra dari kamera
    image = camera.getImage()
    width = camera.getWidth()
    height = camera.getHeight()

    # Inisialisasi variabel untuk menentukan apakah ada garis putih di setiap sisi
    left_white_detected = False
    right_white_detected = False

    # Loop melalui setiap pixel dalam citra
    for y in range(height):
        for x in range(width):
            # Ambil nilai intensitas piksel
            pixel_intensity = camera.imageGetGray(image, width, x, y)
            # Jika intensitas piksel lebih besar dari ambang batas putih
            if pixel_intensity > WHITE_THRESHOLD:
                # Tentukan apakah garis putih terdeteksi di sisi kiri atau kanan
                if x < width / 2:
                    left_white_detected = True
                else:
                    right_white_detected = True

    return left_white_detected, right_white_detected

def run_robot():
    # Buat robot instance
    robot = Robot()

    # Dapatkan perangkat
    camera = robot.getDevice("camera")
    camera.enable(10)

    left_motor = robot.getDevice("left wheel motor")
    right_motor = robot.getDevice("right wheel motor")
    left_motor.setPosition(float('inf'))
    right_motor.setPosition(float('inf'))

    # Main loop
    while robot.step(10) != -1:
        # Periksa apakah garis putih terdeteksi di setiap sisi
        left_white_detected, right_white_detected = process_image(camera)

        # Jika tidak ada garis putih di kedua sisi, maju
        if not left_white_detected and not right_white_detected:
            left_motor.setVelocity(0.5)
            right_motor.setVelocity(0.5)
        # Jika ada garis putih di sisi kiri, putar ke kanan
        elif left_white_detected and not right_white_detected:
            left_motor.setVelocity(0.3)
            right_motor.setVelocity(0.5)
        # Jika ada garis putih di sisi kanan, putar ke kiri
        elif not left_white_detected and right_white_detected:
            left_motor.setVelocity(0.5)
            right_motor.setVelocity(0.3)
        # Jika ada garis putih di kedua sisi, maju
        else:
            left_motor.setVelocity(0.5)
            right_motor.setVelocity(0.5)

if __name__ == "__main__":
    run_robot()
