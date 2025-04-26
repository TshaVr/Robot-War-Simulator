/**********|**********|**********|
Program: Battlefield.cpp
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
#include <iostream> 
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <memory> 

using namespace std; 

// Constructor initializes the battlefield with 2D
Battlefield::Battlefield(int w, int h) : width(w), height(h) {
    initializeField(); // Initialize the battlefield
}
void Battlefield::initializeField() {
    field = std::make_unique<char[]>(width * height); // Allocate memory for the field
    for (int i = 0; i < width * height; ++i) {
        field[i] = '.';
    }
}

void Battlefield::clearField() {
    field.reset();
}
// Destructor frees dynamically allocated memory
Battlefield::~Battlefield() {
     clearField();
}


int Battlefield::getWidth() const {
    return width;  
}

int Battlefield::getHeight() const {
    return height;  
}

// Place a robot on the battlefield
void Battlefield::placeRobot(std::unique_ptr<Robot> robot) {
    int x = robot->getX();
    int y = robot->getY();
    
    if (!isValidPosition(x, y)) {
        std::cerr << "Error: Attempted to place robot at invalid position (" << x << ", " << y << ")." << std::endl;
        return;
    }
    
    if (isOccupied(x, y)) {
        std::cerr << "Error: Position (" << x << ", " << y << ") is already occupied." << std::endl;
        return;
    }
    
    field[y * width + x] = robot->getName()[0]; // Use the first character of the robot's name
    robots.enqueue(std::move(robot)); // Add robot to the queue
}


// Remove a robot from the battlefield
void Battlefield::removeRobot(int x, int y) {
    if (isValidPosition(x, y)) {
        field[y * width + x] = '.';
        Queue tempQueue;
        while (!robots.isEmpty()) {
            std::unique_ptr<Robot> robot = robots.dequeue();
            if (robot && robot->getX() == x && robot->getY() == y) {
                continue;
            }
            tempQueue.enqueue(std::move(robot));
        }
        robots = std::move(tempQueue);
    }
}


// Check if a position is occupied by a robot
bool Battlefield::isOccupied(int x, int y) const {
    return isValidPosition(x, y) && field[y * width + x] != '.';
}

// Check if a position is within the battlefield boundaries
bool Battlefield::isValidPosition(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}


// Update a robot's position on the battlefield
void Battlefield::updatePosition(Robot* robot, int newX, int newY) {
    if (robot && isValidPosition(newX, newY)) {
        int oldX = robot->getX();
        int oldY = robot->getY();

        if (isValidPosition(oldX, oldY)) {
            // Clear old position
            field[oldY * width + oldX] = '.';
        }

        // Update robot's position
        robot->setX(newX);
        robot->setY(newY);

        // Place robot in new position
        if (isValidPosition(newX, newY) && !isOccupied(newX, newY)) {
            field[newY * width + newX] = robot->getName()[0]; // Update field with robot's symbol
        } else {
            std::cerr << "Error: Attempted to update robot to invalid or occupied position." << std::endl;
            
        }
    }
}

Robot* Battlefield::getRobotAt(int x, int y) const {
    if (!isValidPosition(x, y)) return nullptr; // Add bounds check
    Queue::RobotNode* current = robots.getRobots();
    while (current) {
        if (current->robot->getX() == x && current->robot->getY() == y) {
            return current->robot.get();
        }
        current = current->next.get();
    }
    return nullptr;
}

// Display the battlefield
void Battlefield::display(std::ostream& ostream) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Robot* robot = getRobotAt(x, y);
            if (robot != nullptr) {
                ostream << robot->getName()[0] << " ";
            } else {
                ostream << field[y * width + x] << " ";
            }
        }
        ostream << std::endl;
    }
}


