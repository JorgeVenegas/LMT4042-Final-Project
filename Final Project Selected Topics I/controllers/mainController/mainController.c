#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <webots/robot.h>
#include <webots/camera.h>
#include <webots/compass.h>
#include <webots/gps.h>
#include <webots/gyro.h>
#include <webots/inertial_unit.h>
#include <webots/keyboard.h>
#include <webots/led.h>
#include <webots/motor.h>
#include <webots/accelerometer.h>

#define SIGN(x) ((x) > 0) - ((x) < 0)
#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))
#define PI 3.14159265358979323846

int errorCounter = 0;
int checkpointCount = 0;
struct Coordinates { int x; int y; };

void calculateDifference(double xCurrent, double yCurrent, double angle, double xDesired, double yDesired, double* pitch, double* roll, double* yaw, int* rotating, double* yawVelocity, double* error) {
    double deltaX = xDesired - xCurrent;
    double deltaY = yDesired - yCurrent;
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    double destinationAngle = atan2(deltaY, deltaX);
    double errorAngle = angle - destinationAngle;
    if (errorAngle < -PI || errorAngle > PI) {
        errorAngle = destinationAngle + angle;
    }
    double kpYaw = -1;
    double kiYaw = 0.5;
    double kdYaw = 0.0;
    *yaw = CLAMP(kpYaw * errorAngle + kiYaw * errorAngle + kdYaw * errorAngle, -1, 1);
    double meanError = 0;
    if (*rotating == 1) {
        error[errorCounter] = errorAngle;
        errorCounter++;
        if (errorCounter == 1000) {
            errorCounter = 0;
            checkpointCount = 1;
        }
        if (checkpointCount == 0) {
            for (int i = 0; i < errorCounter; i++) {
                meanError += error[i];
            }
            meanError /= errorCounter;
        } else {
            for (int i = 0; i < 1000; i++) {
                meanError += error[i];
            }
            meanError /= 1000;
        }
        if (!((meanError < -0.0005 || meanError > 0.0005) && (*yawVelocity < -0.00005 || *yawVelocity > 0.00005))) {
            *rotating = 0;
        }
    }
    if (*rotating == 0) {
        double kpPitch = 0.3;
        double kiPitch = -0.005;
        double kdPitch = 0.0;
        *pitch = -CLAMP(kpPitch * distance + kiPitch * distance + kdPitch * distance, -2, 2);
    }
}

int main(int argc, char** argv) {
    wb_robot_init();
    int timeStep = (int)wb_robot_get_basic_time_step();

    // Get and enable devices.
    WbDeviceTag camera = wb_robot_get_device("camera");
    wb_camera_enable(camera, timeStep);
    WbDeviceTag frontLeftLed = wb_robot_get_device("front left led");
    WbDeviceTag frontRightLed = wb_robot_get_device("front right led");
    WbDeviceTag imu = wb_robot_get_device("inertial unit");
    wb_inertial_unit_enable(imu, timeStep);
    WbDeviceTag gps = wb_robot_get_device("gps");
    wb_gps_enable(gps, timeStep);
    WbDeviceTag compass = wb_robot_get_device("compass");
    wb_compass_enable(compass, timeStep);
    WbDeviceTag gyro = wb_robot_get_device("gyro");
    wb_gyro_enable(gyro, timeStep);
    wb_keyboard_enable(timeStep);
    WbDeviceTag cameraRollMotor = wb_robot_get_device("camera roll");
    WbDeviceTag cameraPitchMotor = wb_robot_get_device("camera pitch");
    WbDeviceTag cameraYawMotor = wb_robot_get_device("camera yaw");  // Not used in this example.

    // Get propeller motors and set them to velocity mode.
    WbDeviceTag frontLeftMotor = wb_robot_get_device("front left propeller");
    WbDeviceTag frontRightMotor = wb_robot_get_device("front right propeller");
    WbDeviceTag rearLeftMotor = wb_robot_get_device("rear left propeller");
    WbDeviceTag rearRightMotor = wb_robot_get_device("rear right propeller");
    WbDeviceTag motors[4] = { frontLeftMotor, frontRightMotor, rearLeftMotor, rearRightMotor };
    int motorIndex;
    for (motorIndex = 0; motorIndex < 4; ++motorIndex) {
        wb_motor_set_position(motors[motorIndex], INFINITY);
        wb_motor_set_velocity(motors[motorIndex], 10.0);
    }
    struct Coordinates coordinatesArray[12] = {
        {-33, 55},  
        {-33, 95},
        {60, 95},
        {60, 50},
        {60, 95},
        {-33, 95},
        {-33, -20},
        {-65, -20},
        {-65, -90},
        {-115, -90},
        {-115, 80},
        {-85, 80},
    };

    size_t sizePoints = sizeof(coordinatesArray) / sizeof(coordinatesArray[0]);
    int currentPoint = 0;
    int rotationStatus = 1;
    double errors[1000];
    for (int i = 0; i < 1000; i++) {
        errors[i] = 0.0;
    }

    while (wb_robot_step(timeStep) != -1) {  
        if (wb_robot_get_time() > 1.0)
            break;
    }

    // Constants, empirically found.
    const double verticalThrust = 68.5;  // With this thrust, the drone lifts.
    const double verticalOffset = 0.6;   // Vertical offset where the robot actually targets to stabilize itself.
    const double verticalP = 3.0;        // P constant of the vertical PID.
    const double rollP = 50.0;           // P constant of the roll PID.
    const double pitchP = 50.0;          // P constant of the pitch PID.
    double targetAltitude = 1.5;  // The target altitude.

    while (wb_robot_step(timeStep) != -1) {  // Main loop

        const double currentTime = wb_robot_get_time();  // in seconds.

        // Retrieve robot position using the sensors.
        const double roll = wb_inertial_unit_get_roll_pitch_yaw(imu)[0];
        const double pitch = wb_inertial_unit_get_roll_pitch_yaw(imu)[1];
        const double yaw = wb_inertial_unit_get_roll_pitch_yaw(imu)[2];
        const double xCoordinate = wb_gps_get_values(gps)[0];
        const double yCoordinate = wb_gps_get_values(gps)[1];
        const double currentAltitude = wb_gps_get_values(gps)[2];
        const double rollVelocity = wb_gyro_get_values(gyro)[0];
        const double pitchVelocity = wb_gyro_get_values(gyro)[1];
        const double yawVelocity = wb_gyro_get_values(gyro)[2];

        // Transform the keyboard input to disturbances on the stabilization algorithm.
        double rollDisturbance = 0.0;
        double pitchDisturbance = 0.0;
        double yawDisturbance = 0.0;

        if (currentTime > 5) {
            calculateDifference(xCoordinate, yCoordinate, yaw, coordinatesArray[currentPoint].x, coordinatesArray[currentPoint].y, &pitchDisturbance, &rollDisturbance, &yawDisturbance, &rotationStatus, &yawVelocity, errors);

            if ((pitchDisturbance > -0.15 && pitchDisturbance < 0.15) &&
                (rollDisturbance > -0.15 && rollDisturbance < 0.15) &&
                rotationStatus == 0) {
                double realTime = currentTime;
                errorCounter = 0;
                checkpointCount = 0;
                rotationStatus = 1;

                if (currentPoint < 50) {
                    currentPoint += 1;
                    while (wb_robot_step(timeStep) != -1) {
                        if (wb_robot_get_time() - realTime > 2.0)
                            break;
                    }
                } else {
                    while (wb_robot_step(timeStep) != -1) {
                        if (wb_robot_get_time() - realTime > 5.0)
                            break;
                    }
                }
            }
        }

        // Compute the roll, pitch, yaw, and vertical inputs.
        const double rollInput = rollP * CLAMP(roll, -1.0, 1.0) + rollVelocity + rollDisturbance;
        const double pitchInput = pitchP * CLAMP(pitch, -1.0, 1.0) + pitchVelocity + pitchDisturbance;
        const double yawInput = yawDisturbance;
        const double clampedAltitudeDifference = CLAMP(targetAltitude - currentAltitude + verticalOffset, -1.0, 1.0);
        const double verticalInput = verticalP * pow(clampedAltitudeDifference, 3.0);

        // Actuate the motors taking into consideration all the computed inputs.
        const double frontLeftMotorInput = verticalThrust + verticalInput - rollInput + pitchInput - yawInput;
        const double frontRightMotorInput = verticalThrust + verticalInput + rollInput + pitchInput + yawInput;
        const double rearLeftMotorInput = verticalThrust + verticalInput - rollInput - pitchInput + yawInput;
        const double rearRightMotorInput = verticalThrust + verticalInput + rollInput - pitchInput - yawInput;

        // Set velocities for motors
        wb_motor_set_velocity(frontLeftMotor, frontLeftMotorInput);
        printf("frontLeftMotorInput:%f ", frontLeftMotorInput);
        wb_motor_set_velocity(frontRightMotor, -frontRightMotorInput);
        printf("frontRightMotorInput:%f ", -frontRightMotorInput);
        wb_motor_set_velocity(rearLeftMotor, -rearLeftMotorInput);
        printf("rearLeftMotorInput:%f ", -rearLeftMotorInput);
        wb_motor_set_velocity(rearRightMotor, rearRightMotorInput);
        printf("rearRightMotorInput:%f ", rearRightMotorInput);

        // Landing the drone.
        if (currentPoint == 12) {
            double targetAltitude = 0.0;
            const double rollInput = rollP * CLAMP(roll, -1.0, 1.0) + rollVelocity + rollDisturbance;
            const double pitchInput = pitchP * CLAMP(pitch, -1.0, 1.0) + pitchVelocity + pitchDisturbance;
            const double yawInput = yawDisturbance;
            const double clampedAltitudeDifference = CLAMP(targetAltitude - currentAltitude + verticalOffset, -1.0, 1.0);
            const double verticalInput = verticalP * pow(clampedAltitudeDifference, 3.0);
            const double frontLeftMotorInput = verticalThrust + verticalInput - rollInput + pitchInput - yawInput;
            const double frontRightMotorInput = verticalThrust + verticalInput + rollInput + pitchInput + yawInput;
            const double rearLeftMotorInput = verticalThrust + verticalInput - rollInput - pitchInput + yawInput;
            const double rearRightMotorInput = verticalThrust + verticalInput + rollInput - pitchInput - yawInput;

            wb_motor_set_velocity(frontLeftMotor, frontLeftMotorInput);
            wb_motor_set_velocity(frontRightMotor, -frontRightMotorInput);
            wb_motor_set_velocity(rearLeftMotor, -rearLeftMotorInput);
            wb_motor_set_velocity(rearRightMotor, rearRightMotorInput);

            if (currentAltitude < 0.1) {
                wb_motor_set_velocity(frontLeftMotor, 0.0);
                wb_motor_set_velocity(frontRightMotor, 0.0);
                wb_motor_set_velocity(rearLeftMotor, 0.0);
                wb_motor_set_velocity(rearRightMotor, 0.0);

                while (wb_robot_step(timeStep) != -1) {  // Wait one second.
                    if (wb_robot_get_time() > 1.0)
                        break;
                }
            }
        }
    }

    wb_robot_cleanup();
    return EXIT_SUCCESS;
}
