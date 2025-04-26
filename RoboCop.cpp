/**********|**********|**********|
Program: RoboCop.cpp
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

#include "RoboCop.h" 
#include "TerminatorRoboCop.h"
#include "Battlefield.h"
using namespace std; 

RoboCop::RoboCop(std::string name, int x, int y, Battlefield* bf)
    : Robot(name, x, y, bf), killers(0) {}

RoboCop::~RoboCop() {}


void RoboCop::look(int x, int y, std::ofstream& outputFile) {
  for (int i = x - 1; i <= x + 1; ++i) {
    for (int j = y - 1; j <= y + 1; ++j) {
      if (battlefield->isValidPosition(i, j)) {
        if (battlefield->isOccupied(i, j)) {
          Robot* target = battlefield->getRobotAt(i, j);
          if (target && target != this) {
            outputFile << name << " sees an enemy robot at (" << i << ", " << j << ")" << std::endl;
          }
        } else {
          outputFile << name << " sees an empty cell at (" << i << ", " << j << ")" << std::endl;
        }
      }
    }
  }
}

void RoboCop::move(int x, int y, std::ofstream& outputFile) {
    int newX = positionX + x;
    int newY = positionY + y;
    
    // Check if the new position is within the battlefield bounds and unoccupied
    if (battlefield->isValidPosition(newX, newY) && !battlefield->isOccupied(newX, newY)) {
        // Move the robot to the new position
        battlefield->updatePosition(this, newX, newY);
        positionX = newX;
        positionY = newY;
        outputFile << name << " moves to (" << positionX << ", " << positionY << ")" << std::endl;
    } else {
        outputFile << name << " cannot move to (" << newX << ", " << newY << ")" << std::endl;
    }
}

void RoboCop::step(int x, int y, std::ofstream& outputFile) {
    // RoboCop does not step on other robots until upgraded to TerminatorRoboCop
}

void RoboCop::fire(int x, int y, std::ofstream& outputFile) {
    int targetX = positionX + x;
    int targetY = positionY + y;

    if (abs(x) + abs(y) <= 10 && !(x == 0 && y == 0)) { //
        /* The target position (x, y) is within the maximum city distance of 10 
        and the robot does not fire at its own position.*/
        if (battlefield->isValidPosition(targetX, targetY)) {
            if (battlefield->isOccupied(targetX, targetY)) {
                Robot* target = battlefield->getRobotAt(targetX, targetY);
                if (target && target != this) { // Check if target is valid
                target->decrementLives();
                outputFile << name << " fires at (" << targetX << ", " << targetY << ") and hits " << target->getName() << std::endl;
                if (!target->isAlive()) {
                    outputFile << target->getName() << " has been destroyed!" << std::endl;
                    battlefield->removeRobot(targetX, targetY);
                    killers++;
                    if (killers == 3) {
                        upgrade(outputFile);
                    }
                }
              }
            } else {
                outputFile << name << " fires at (" << targetX << ", " << targetY << ") but there is no target" << std::endl;
            }
        } else {
                outputFile << name << " cannot fire at an invalid position (" << targetX << ", " << targetY << ")" << std::endl;
        }
    }
}

void RoboCop::takeAction(std::ofstream& outputFile) {


    // Look around
    look(positionX, positionY, outputFile); 
    // Move to a random adjacent cell
    int moveX = rand() % 3 - 1; // -1, 0, or 1
    int moveY = rand() % 3 - 1;
    move(moveX, moveY, outputFile);

    // Fire at three random positions 
    for (int i = 0; i < 3; ++i) {
        int fireX = rand() % 21 - 10; // -10 to 10
        int fireY = rand() % 21 - 10;
        if (abs(fireX) + abs(fireY) <= 10) {
            fire(fireX, fireY, outputFile);
        }
    }
    
}

void RoboCop::upgrade(std::ofstream& outputFile) {
    // Create a new TerminatorRoboCop at the same position
    auto terminatorRoboCop = std::make_unique<TerminatorRoboCop>(getName(), getX(), getY(), battlefield);
    
    // Replace this RoboCop with the new TerminatorRoboCop in the battlefield
    battlefield->replaceRobot(*this, std::move(terminatorRoboCop));
    
    outputFile << "RoboCop " << getName() << " has been upgraded to TerminatorRoboCop at (" << getX() << ", " << getY() << ")" << std::endl;
}
