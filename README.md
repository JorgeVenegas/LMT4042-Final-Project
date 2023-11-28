# Drone Control Code Simulation in Webots

## Background 

Today, drones have become an indispensable tool in natural disasters and emergencies. The ability to reach remote and dangerous areas inaccessible to humans and provide real-time aerial vision has enabled faster and more effective responses to natural and man-made disasters. The article will discuss the different uses of drones in emergency situations and their importance in humanitarian operations.

Drones have been used in various emergency situations such as floods, earthquakes, wildfires, and landslides. In addition, drones are also used in search and rescue missions for people lost, missing, or trapped in collapsed buildings. In such cases, drones can provide search and rescue teams with high-resolution imagery so they know where to look and how to perform a rescue. In disaster mitigation, drones are also used to collect data and create accurate maps that help disaster management teams plan and coordinate actions during emergencies. Maps created by drones can show the location of survivors, affected areas, and access routes for rescue teams. In addition, drones can provide real-time information on the evolution of wildfires, helping authorities make quick and effective decisions to control the spread of fires.
In the humanitarian sector, drones can provide logistical support, delivering supplies to remote and hard-to-reach areas where roads and bridges have been destroyed or are impassable. At the same time, drones are also used to provide medicine and food to people in hard-to-reach areas and to quickly help people in dangerous places.

All in all, drones are becoming an increasingly valuable tool in the event of natural disasters and emergencies. The ability to provide real-time terrain visibility, accurate mapping, and, in some situations, supply supply has proven critical in saving lives and minimizing casualties in these situations. As drones are developed and improved, their use in disasters and emergencies is likely to continue to increase, thus ensuring more timely and effective assistance to affected populations.

<img width="980" alt="image" src="https://github.com/JorgeVenegas/LMT4042-Final-Project/assets/32798923/5f94390a-b4bf-4fa8-98e8-ed5765eb01c5">


This code is designed to control a drone's movement and navigation in a simulated environment using the Webots robotics simulation platform. The drone is equipped with various sensors, including GPS, inertial unit, and gyro, to gather information about its position, orientation, and altitude.

View demo here: https://winliveudlap-my.sharepoint.com/:v:/g/personal/jorge_venegaslo_udlap_mx/EUt71LOsfvRAn5LaVfI3KToBl8rsU1HIRBZLuhUjaNABBg?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0RpcmVjdCJ9fQ&e=7Ms2rI

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
