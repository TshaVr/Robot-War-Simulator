/**********|**********|**********|
Program: UltimateRobot.cpp
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

#include "UltimateRobot.h" 
#include "Battlefield.h"

using namespace std; 
UltimateRobot::UltimateRobot(std::string name, int x, int y, Battlefield* bf)
    : Robot(name, x, y, bf), TerminatorRoboCop(name, x, y, bf), RoboCop(name, x, y, bf), Terminator(name, x, y, bf), killers(0){}

UltimateRobot::~UltimateRobot() {}

void UltimateRobot::look(int x, int y, std::ofstream& outputFile) {
    TerminatorRoboCop::look(x,y, outputFile);
}
void UltimateRobot::move(int x, int y, std::ofstream& outputFile) {
    TerminatorRoboCop::move(x,y, outputFile);
}

void UltimateRobot::step(int x, int y, std::ofstream& outputFile) {
    // UltimateRobot inherit siep from TerminatorRoboCop
}

void UltimateRobot::fire(int x, int y, std::ofstream& outputFile) {
    int targetX = positionX + x;
    int targetY = positionY + y;

       if (battlefield->isValidPosition(targetX, targetY) && battlefield->isOccupied(targetX, targetY)) {
        Robot* target = battlefield->getRobotAt(targetX, targetY);
        target->decrementLives();
        outputFile << name << " fires at (" << targetX << ", " << targetY << ") and hits " << target->getName() << endl;
        if (!target->isAlive()) {
            outputFile << target->getName() << " has been destroyed!" << endl;
            battlefield->removeRobot(targetX, targetY);
            killers++;
        }
    }
}
void UltimateRobot::takeAction(std::ofstream& outputFile) {
     // Look around
    look(positionX, positionY, outputFile);

    int moveX = rand() % 3 - 1; // -1, 0, or 1
    int moveY = rand() % 3 - 1;

    // Move to the new position
    move(moveX, moveY, outputFile);

     // Fire at three random locations within the battlefield
    for (int i = 0; i < 3; ++i) {
        int fireX = rand() % battlefield->getWidth();
        int fireY = rand() % battlefield->getHeight();
        fire(fireX, fireY, outputFile);
    }
}
