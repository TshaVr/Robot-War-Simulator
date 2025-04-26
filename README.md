
# Robot War Simulator 🤖

## Description
The **Robot War Simulator** is a C++ project that simulates a turn-based robotic battlefield. Robots with various movement, vision, and attack capabilities engage in a series of actions, including looking, moving, and firing, based on predefined rules. The simulation is implemented using object-oriented programming principles like inheritance, polymorphism, and operator overloading, with custom data structures for handling simulation elements.

## Features
- **Turn-based simulation** of robots on a 2D battlefield.
- Multiple robot types (e.g., RoboCop, Terminator, BlueThunder, MadBot) with unique abilities.
- Robots can look, move, fire, and destroy other robots.
- Robots can re-enter the battlefield after being destroyed.
- Simulation is logged in a text file and displayed on screen.
- Custom data structures implemented instead of using C++ STL containers.
- Robots are controlled based on input from a configuration file.

## Design Patterns Used
- **Strategy Pattern**: Different robot behaviors (move, shoot, look) are defined through class hierarchies.
- **Factory Method Pattern**: Robots are created dynamically based on configuration input.

## Installation

1. **Clone this repository**:
    ```bash
    git clone https://github.com/your-username/robot-war-simulator.git
    ```

2. **Compile the C++ files**:
    Ensure you have a C++ compiler (e.g., `g++`):
    ```bash
    g++ -o RobotWarSimulator main.cpp Robot.cpp RobotTypes.cpp -std=c++11
    ```

3. **Run the simulator**:
    ```bash
    ./RobotWarSimulator
    ```

## Usage
1. **Configure the battlefield**:
    - The battlefield size (M x N) and robot configurations are defined in a text file (e.g., `config.txt`).
    - The text file contains the number of robots, their types, names, and starting positions.
  
2. **Simulation**:
    - Run the program to start the simulation.
    - Watch the robot actions and results displayed on the screen.
    - The simulation log will also be saved to a file for reference.

## Example Configuration File (`config.txt`):
```
M by N : 40 50
steps: 300
robots: 5
Madbot Kidd 3 6
RoboTank Jet 12 1
Terminator Alpha 35 20
BlueThunder Beta 20 37
RoboCop Star random random
```

## Custom Data Structures
- **Queue**: Implemented a custom queue to manage robots that are destroyed and need to re-enter the battlefield.
- **Linked List**: Used to track robots' actions in the simulation.
