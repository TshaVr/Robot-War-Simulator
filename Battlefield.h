/**********|**********|**********|
Program: Battlefield.h
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

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <string>
#include <memory>
#include <iostream>
#include "Queue.h"    // Include the custom Queue header
#include "Robot.h"

// Forward declaration of Robot class to avoid circular dependencies
class Robot;

class Battlefield {
private:
    int width;
    int height;
    std::unique_ptr<char[]> field; // Using unique_ptr for 2D array
    void initializeField();
    void clearField(); // Method to clear the battlefield
    Queue robots; // Using custom Queue instead of std::unique_ptr<RobotNode>

public:
    Battlefield(int w, int h); // Constructor
    ~Battlefield(); // Destructor

    int getWidth() const;
    int getHeight() const;

    void placeRobot(std::unique_ptr<Robot> robot); // Method to place a robot on the battlefield
    void removeRobot(int x, int y); // Method to remove a robot from the battlefield
    bool isOccupied(int x, int y) const; // Method to check if a position is occupied by a robot
    bool isValidPosition(int x, int y) const; // Method to check if a position is within the battlefield boundaries
    void updatePosition(Robot* robot, int newX, int newY); // Method to update a robot's position
    Robot* getRobotAt(int x, int y) const; // Method to get a robot at a specific position
    void display(std::ostream& ostream) const; // Method to display the battlefield
     // Replace a robot with another robot
    template <typename RobotType>
    void replaceRobot(Robot& oldRobot, RobotType&& newRobot) {
    int x = oldRobot.getX();
    int y = oldRobot.getY();
    
    this->removeRobot(x, y);  // Assuming these methods are from Battlefield
    
    (*newRobot).setX(x);  // Dereference unique_ptr to access Robot methods
    (*newRobot).setY(y);  // Dereference unique_ptr to access Robot methods
    
    this->placeRobot(std::forward<RobotType>(newRobot));  // Assuming these methods are from Battlefield
}


};

#endif // BATTLEFIELD_H
