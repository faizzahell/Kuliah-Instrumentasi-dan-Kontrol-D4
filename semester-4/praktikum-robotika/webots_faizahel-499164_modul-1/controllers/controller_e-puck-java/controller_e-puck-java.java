// File:          controller_e-puck-java.java
// Date:
// Description:
// Author:
// Modifications:

import com.cyberbotics.webots.controller.Robot;
import com.cyberbotics.webots.controller.Motor;

public class Main {
    private static final int TIME_STEP = 64;

    public static void main(String[] args) {
        // Inisialisasi robot
        Robot robot = new Robot();

        // Dapatkan perangkat motor
        Motor leftMotor = robot.getMotor("left wheel motor");
        Motor rightMotor = robot.getMotor("right wheel motor");

        // Set posisi target motor
        rightMotor.setPosition(20.0);

        // Loop utama
        while (robot.step(TIME_STEP) != -1) {
            // Diperlukan untuk menjalankan simulasi
        }
    }
}
