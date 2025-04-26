/**********|**********|**********|
Program: main.cpp
Course: OOPDS
Trimester: 2420
Name: Mohammed Aamena Mohammed Abdulkarem/ Thirissha Gangatharan / Eng Xin Yee
      Jaroon Hussein Moqbel / Mohammed Yousef Mohammed Abdulkarem
ID: 1221305728 / 1211106376 / 1211105750 / 1221306781 / 1221305727
Lecture Section: TC1L
Tutorial Section: TT3L
Email: 1221305728@student.mmu.edu.my / 1211106376@student.mmu.edu.my / 1211105750@student.mmu.edu.my
       1221306781@student.mmu.edu.my / 1221305727@student.mmu.edu.my
Phone: 011-62237057 / 017-8600821 / 017-8415131 / 013-3592846 / 011-62238871
**********|**********|**********/

#include "Battlefield.h"
#include "Robot.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "MadBot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <memory>
#include <sstream>
#include <vector>
#include <exception>

using namespace std;

void initializeSimulation(const std::string& filename, std::unique_ptr<Battlefield>& bf, int& steps, std::vector<Robot*>& robots) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    std::string line;
    int width = 0, height = 0, numRobots = 0;

    // Read dimensions
    while (std::getline(file, line)) {
        if (line.find("M by N :") == 0) {
            std::stringstream ss(line);
            ss.ignore(20, ':');
            ss >> width >> height;
            bf = std::make_unique<Battlefield>(width, height);
            break;
        }
    }

    // Read steps
    while (std::getline(file, line)) {
        if (line.find("steps:") == 0) {
            std::stringstream ss(line);
            ss.ignore(20, ':');
            ss >> steps;
            break;
        }
    }

    // Read number of robots
    while (std::getline(file, line)) {
        if (line.find("robots:") == 0) {
            std::stringstream ss(line);
            ss.ignore(20, ':');
            ss >> numRobots;
            break;
        }
    }

    // Read robot details and place them in the vector
    std::string robotType, robotName, X, Y;
    for (int i = 0; i < numRobots; ++i) {
        file >> robotType >> robotName >> X >> Y;

        int posX, posY;
        if (X == "random") {
            posX = rand() % width;
        } else {
            posX = std::stoi(X);
        }

        if (Y == "random") {
            posY = rand() % height;
        } else {
            posY = std::stoi(Y);
        }
   Robot* robot = nullptr;
        if (robotType == "RoboCop") {
            robot = new RoboCop(robotName, posX, posY, bf.get());
        } else if (robotType == "Terminator") {
            robot = new Terminator(robotName, posX, posY, bf.get());
        } else if (robotType == "TerminatorRoboCop") {
            robot = new TerminatorRoboCop(robotName, posX, posY, bf.get());
        } else if (robotType == "BlueThunder") {
            robot = new BlueThunder(robotName, posX, posY, bf.get());
        } else if (robotType == "MadBot") {
            robot = new MadBot(robotName, posX, posY, bf.get());
        } else if (robotType == "RoboTank") {
            robot = new RoboTank(robotName, posX, posY, bf.get());
        } else if (robotType == "UltimateRobot") {
            robot = new UltimateRobot(robotName, posX, posY, bf.get());
        } else {
            throw std::runtime_error("Unknown robot type: " + robotType);
        }

        robots.push_back(robot);
        std::cout << "Placed robot " << robotName << " of type " << robotType << " at (" << posX << ", " << posY << ")\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::unique_ptr<Battlefield> bf;
    int steps = 0;
    std::vector<Robot*> robots;
    std::ofstream outputFile("output.txt");

    try {
        initializeSimulation("robots.txt", bf, steps, robots);

        // Run simulation for the specified number of steps
        for (int i = 1; i <= steps; ++i) {
            // Output current step
            outputFile << "Step " << i << ":\n";
            cout << "Step " << i << ":\n";

            // Process each robot in the vector
            for (Robot* robot : robots) {
                // Perform action for each robot
                robot->takeAction(outputFile);

                // Assuming posX and posY are updated by takeAction method
                int posX = robot->getX();
                int posY = robot->getY();

                // Check if the position is valid on the battlefield
                if (bf->isValidPosition(posX, posY)) {
                    // Update the robot's position on the battlefield
                    bf->updatePosition(robot, posX, posY);
                    cout << "Updated position of robot " << robot->getName() << " of type " << typeid(*robot).name() << " to (" << posX << ", " << posY << ")\n";
                } else {
                    cout << "Cannot update position of robot " << robot->getName() << " to (" << posX << ", " << posY << ") because the position is invalid.\n";
                }
            }

            // Output final state of the battlefield after each step
            bf->display(outputFile);
            

            // Remove destroyed robots from the vector
            auto it = robots.begin();
            while (it != robots.end()) {
                if (!(*it)->isAlive()) {
                    delete *it;
                    it = robots.erase(it);
                } else {
                    ++it;
                }
            }
        }

        // Cleanup allocated memory for remaining robots
        for (Robot* robot : robots) {
            delete robot;
        }
        robots.clear();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    outputFile.close();
    return 0;
}