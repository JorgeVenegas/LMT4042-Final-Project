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

# Project World Design

The design of the project focused on simulating a flooding scenario in a virtual city environment measuring 250 m x 250 m. The primary objective was to create a challenging and realistic simulation where a drone would assist people strategically placed within the flooded city.

## Virtual Environment Features

### 1. **City Layout:**
   - The virtual environment replicates a city affected by flooding, with a realistic depiction of water covering the streets and buildings.
   - A 250 m x 250 m area was created to simulate the city layout.

### 2. **Strategic Targets:**
   - Within the flooded city, several targets were strategically placed, representing people in need of assistance.
   - The drone's primary purpose was to navigate the virtual environment and provide help to these targets during the simulation.

### 3. **Building Nodes:**
   - Various building nodes were strategically placed to expand the city's infrastructure and increase the simulation's complexity.
   - Each building node had unique characteristics that impacted the drone's movement, such as varying heights and the presence of obstacles.

## Simulation Objectives

1. **Assisting People in Need:**
   - The primary goal of the drone was to assist individuals strategically placed within the virtual city, simulating a real-life emergency scenario.

2. **Code Adaptability to Environment:**
   - The drone's code had to consider the characteristics of building nodes, such as height and obstacles, when navigating through the simulated environment.

## Outcome and Analysis

Through this carefully designed virtual world, the project achieved a challenging and realistic simulation. It provided a platform to assess the drone's abilities in responding to emergency situations, specifically flooding in a city. The combination of the drone's displacement code with the intricacies of the simulated environment allowed for a detailed analysis of its behavior and improved its response capacity in real-life emergency scenarios.

This project serves as a valuable tool for testing and enhancing drone capabilities in disaster response, contributing to the development of more effective and reliable unmanned aerial systems for humanitarian purposes.

# Project Conclusion

In conclusion, the emergency simulation project proved to be a success as it effectively met the proposed objectives. The combination of a thoughtfully designed virtual world and meticulously crafted drone code facilitated comprehensive testing of the drone's capabilities, particularly its ability to assist individuals in emergency scenarios like flooding.

## Key Achievements

### 1. **Objective Fulfillment:**
   - The simulation project successfully achieved its primary objectives, evaluating the drone's response in a simulated flood emergency and its effectiveness in assisting affected individuals.

### 2. **World Design Impact:**
   - The intricately designed virtual environment, featuring a flooded city and strategically placed targets, provided a realistic and challenging scenario for the drone to navigate.

### 3. **Code Development Significance:**
   - The development of the drone's code was crucial in ensuring accurate and efficient movement, enabling timely assistance to those affected by the simulated emergency.

### 4. **Complexity and Responsiveness Improvement:**
   - The inclusion of diverse building nodes increased the complexity of the simulation, challenging the drone to adapt and improve its responsiveness in a dynamic environment.

## Integration of Elements

The synergy between the well-designed virtual world and the precisely crafted drone code yielded a realistic and accurate emergency simulation. This integrated approach allowed for a detailed evaluation of the drone's behavior and response capabilities, contributing to advancements in unmanned aerial systems for humanitarian purposes.

This project stands as a testament to the effectiveness of combining realistic simulation design with optimized drone code, providing valuable insights for further developments in emergency response technologies.
