# Drone Control Code Readme

This code is designed to control a drone's movement and navigation in a simulated environment using the Webots robotics simulation platform. The drone is equipped with various sensors, including GPS, inertial unit, and gyro, to gather information about its position, orientation, and altitude.

## Functionality

### Navigation

The drone follows a predefined set of coordinates, simulating a delivery route. The coordinates are stored in the `coordinatesArray` variable, and the drone navigates through these points, adjusting its pitch, roll, and yaw to reach the desired positions.

### PID Control

The code implements a PID control system to stabilize the drone during navigation. It calculates the difference between the current and desired positions, adjusts the pitch, roll, and yaw accordingly, and ensures a smooth transition between waypoints.

### Altitude Control

The drone maintains a target altitude using a vertical PID controller. It adjusts thrust and pitch to control the altitude, ensuring a stable flight.

### Landing

After reaching the final waypoint, the drone descends to the ground and lands. It gradually reduces altitude and motor velocities to safely land on the ground.

## How to Use

1. **Setting Up the Environment:** Ensure that Webots is installed and configured. Import the drone model into Webots and set up the necessary sensors and actuators.

2. **Running the Code:** Copy and paste the provided C code into your Webots controller script. Compile and run the simulation in Webots to observe the drone's navigation.

3. **Simulation Control:** The code includes logic to start the drone after a brief initialization period. Adjust the simulation duration and parameters as needed.

4. **Monitoring Output:** The console output provides information about the drone's position, orientation, altitude, and motor inputs. Use this information to monitor the drone's behavior during the simulation.

Note: The code assumes a specific drone model and sensor configuration in Webots. Adjustments may be needed for different drone models or sensor setups.

Feel free to explore and modify the code to experiment with different navigation scenarios or integrate additional functionalities.
