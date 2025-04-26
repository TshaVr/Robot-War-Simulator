/**********|**********|**********|
Program: Terminator.cpp
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

#include "Terminator.h" 
#include "TerminatorRoboCop.h"
#include "Battlefield.h"
using namespace std; 

Terminator::Terminator(std::string name, int x, int y, Battlefield* bf)
    : Robot(name, x, y, bf),  killers(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
    }

Terminator::~Terminator() {}

void Terminator::look(int x, int y, std::ofstream& outputFile) {
    
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (battlefield->isValidPosition(i, j)) {
                if (battlefield->isOccupied(i, j)) {
                     Robot* target = battlefield->getRobotAt(i, j);
                     if (target && target != this) {
                    outputFile << name << " sees an enemy robot at (" << i << ", " << j << ")" << std::endl;}
                } else {
                    outputFile << name << " sees an empty cell at (" << i << ", " << j << ")" << std::endl;
                }
            }
        }
    }
}
void Terminator::move(int x, int y, std::ofstream& outputFile) {
    int targetX = positionX + x;
    int targetY = positionY + y;

    if (battlefield->isValidPosition(targetX, targetY)) {
        if (battlefield->isOccupied(targetX, targetY)) {
            step(targetX, targetY,outputFile);
        } else {
            battlefield->updatePosition(this, targetX, targetY);
            positionX = targetX;
            positionY = targetY;
            outputFile << name << " moves to (" << targetX << ", " << targetY << ")" << std::endl;
        }
    } else {
        outputFile << name << " cannot move to an invalid position (" << targetX << ", " << targetY << ")" << std::endl;
    }
}

void Terminator::step(int x, int y, std::ofstream& outputFile) {
    Robot* target = battlefield->getRobotAt(x, y);
    if (target) { // Check if target is valid
        target->decrementLives();
        outputFile << name << " steps on (" << x << ", " << y << ") and terminates " << target->getName() << std::endl;
        if (!target->isAlive()) {
            outputFile << target->getName() << " has been destroyed!" << std::endl;
            battlefield->removeRobot(x, y);
            killers++;
            if (killers == 3) {
                upgrade(outputFile);
            }
        }
    }
}

void Terminator::fire(int x, int y, std::ofstream& outputFile) {
    // Terminator does not fire
}

void Terminator::takeAction(std::ofstream& outputFile) {
    // Look around
    look(positionX,positionY, outputFile); 
    // Move to a random adjacent cell
    int moveX = rand() % 3 - 1; 
    int moveY = rand() % 3 - 1;
    move(moveX, moveY, outputFile); 
    
}

void Terminator::upgrade(std::ofstream& outputFile) {
    // Create a new TerminatorRoboCop at the same position
    auto terminatorRoboCop = std::make_unique<TerminatorRoboCop>(getName(), getX(), getY(), battlefield);
    
    // Replace this Terminator with the new TerminatorRoboCop in the battlefield
    battlefield->replaceRobot(*this, std::move(terminatorRoboCop));
    
    // Output upgrade message
    outputFile << "Terminator " << getName() << " has been upgraded to TerminatorRoboCop at (" << getX() << ", " << getY() << ")" << std::endl;
}
