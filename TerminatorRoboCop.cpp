/**********|**********|**********|
Program: TerminatorRoboCop.cpp
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

#include "TerminatorRoboCop.h" 
#include "UltimateRobot.h"
#include "Battlefield.h"
using namespace std; 

TerminatorRoboCop::TerminatorRoboCop(std::string name, int x, int y, Battlefield* bf)
    : Robot(name, x, y, bf), RoboCop(name, x, y, bf), Terminator(name, x, y, bf), killers(0){}

TerminatorRoboCop::~TerminatorRoboCop() {}

void TerminatorRoboCop::look(int x, int y, std::ofstream& outputFile) {
    RoboCop::look(x, y, outputFile);
}

void TerminatorRoboCop::move(int x, int y, std::ofstream& outputFile) {
    int targetX = positionX + x;
    int targetY = positionY + y;
    
    if (battlefield->isValidPosition(targetX, targetY)) {
        if (battlefield->isOccupied(targetX, targetY)) {
            // If the target position is occupied, step like a Terminator
            Terminator::step(x, y, outputFile);
        } else {
            // If the target position is unoccupied, move and fire like a RoboCop
            RoboCop::move(x, y, outputFile);
        }
    } else {
        // If the target position is invalid, inform about it
        outputFile << getName() << " cannot move to (" << targetX << ", " << targetY << ") as it's an invalid position" << endl;
    }
}

void TerminatorRoboCop::step(int x, int y, std::ofstream& outputFile) {
   // TerminatorRoboCop inherits step from Terminator
    
}

void TerminatorRoboCop::fire(int x, int y, std::ofstream& outputFile) {
    // TerminatorRoboCop inherit fire from RoboCop 
  
}

void TerminatorRoboCop::takeAction(std::ofstream& outputFile) {
    //look around
    look(positionX, positionY, outputFile);

    int moveX = rand() % 3 - 1; // -1, 0, or 1
    int moveY = rand() % 3 - 1;
    move(moveX, moveY, outputFile);

    for (int i = 0; i < 3; ++i) {
        int fireX = rand() % 21 - 10; // -10 to 10
        int fireY = rand() % 21 - 10;
        if (abs(fireX) + abs(fireY) <= 10) {
            fire(fireX, fireY, outputFile);
        }
    }
    // Check if the number of killers is 3 for upgrade
    if (killers == 3 ) {
        cout << getName() << " has been upgraded to UltimateRobot!" << endl;
        upgrade(outputFile);
    }
}

void TerminatorRoboCop::upgrade(std::ofstream& outputFile) {
    battlefield->replaceRobot(*this, std::make_unique<UltimateRobot>(getName(), getX(), getY(), battlefield));
    outputFile << "TerminatorRoboCop " << getName() << " has been upgraded to UltimateRobot at (" << getX() << ", " << getY() << ")" << std::endl;
}

