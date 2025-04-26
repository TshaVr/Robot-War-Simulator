/**********|**********|**********|
Program: RoboTank.cpp
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

#include "RoboTank.h" 

using namespace std; 
RoboTank::RoboTank(std::string name, int x, int y, Battlefield* bf)
    : Robot(name, x, y, bf), destroyedRobots(0) {
    /* Seed the random number generator ensure that the sequence of random numbers 
    is different every time you run the program */
        srand(static_cast<unsigned int>(time(nullptr)));
    }

RoboTank::~RoboTank() {}

void RoboTank::look(int x, int y, std::ofstream& outputFile) {
    // RoboTank does not look 
}

void RoboTank::move(int x, int y, std::ofstream& outputFile) {
     // RoboTank does not move 
}

void RoboTank::step(int x, int y, std::ofstream& outputFile) {
     // RoboTank does not step 
}

void RoboTank::fire(int x, int y, std::ofstream& outputFile) {
    
    // Generate random coordinates within the battlefield dimensions
    int targetX = rand() % battlefield->getWidth();
    int targetY = rand() % battlefield->getHeight();

    // Check if the target cell is occupied
    if (battlefield->isOccupied(targetX, targetY)) {
        Robot* target = battlefield->getRobotAt(targetX, targetY);
        target->decrementLives(); // Decrement the lives of the target robot
        outputFile << name << " fires at (" << targetX << ", " << targetY << ") and hits " << target->getName() << std::endl;

        // Check if the target robot is destroyed
        if (!target->isAlive()) {
            outputFile << target->getName() << " has been destroyed!" << std::endl;
            destroyedRobots++;

            // Check if RoboTank has destroyed 3 robots
            if (destroyedRobots == 3) {
                // Upgrade RoboTank to UltimateRobot
                upgrade(outputFile);
            }
        }
    } else {
        // Output message if the target cell is not occupied
        outputFile << name << " fires at (" << targetX << ", " << targetY << ") but there is no target" << std::endl;
    
    }
}

void RoboTank::takeAction(std::ofstream& outputFile) {
    fire(positionX, positionY, outputFile);
}

void RoboTank::upgrade(std::ofstream& outputFile) {
    // Create a new UltimateRobot at the same position
    auto ultimateRobot = std::make_unique<UltimateRobot>(getName(), getX(), getY(), battlefield);
    
    // Replace this RoboTank with the new UltimateRobot in the battlefield
    battlefield->replaceRobot(*this, std::move(ultimateRobot));
    
    // Output upgrade message
    outputFile << "RoboTank " << getName() << " has been upgraded to UltimateRobot at (" << getX() << ", " << getY() << ")" << std::endl;
}

