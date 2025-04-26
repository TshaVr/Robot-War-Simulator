/**********|**********|**********|
Program: MadBot.cpp
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

#include "MadBot.h" 


using namespace std; 

MadBot::MadBot(std::string name, int x, int y, Battlefield* bf)
    : Robot(name, x, y, bf) {
    // Seed the random number generator 
    srand(time(nullptr));
    }

MadBot::~MadBot() {}

void MadBot::look(int x, int y, std::ofstream& outputFile) {
    // MadBot does not look 
}

void MadBot::move(int x, int y, std::ofstream& outputFile) {
    // MadBot does not move 
}

void MadBot::step(int x, int y, std::ofstream& outputFile) {
    // MadBot does not step 
}

void MadBot::fire(int x, int y, std::ofstream& outputFile) {
    // Define arrays for the relative coordinates of neighboring cells
    int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    

    // Generate a random index for the neighboring cells 0-7
    int randomIndex = rand() % 8;

    // Determine the coordinates of the randomly selected neighboring cell
    int targetX = x + dx[randomIndex];
    int targetY = y + dy[randomIndex];

    // Check if the target cell is valid and occupied
    if (battlefield->isValidPosition(targetX, targetY)) {
        if (battlefield->isOccupied(targetX, targetY)) {
            Robot* target = battlefield->getRobotAt(targetX, targetY);
            target->decrementLives(); // Decrement the lives of the target robot
            outputFile << name << " fires at (" << targetX << ", " << targetY << ") and hits " << target->getName() << std::endl;

            // Check if the target robot is destroyed
            if (!target->isAlive()) {
                outputFile << target->getName() << " has been destroyed!" << std::endl;
                battlefield->removeRobot(targetX, targetY);
                destroyedRobots++;

                // Check if MadBot has destroyed 3 robots
                if (destroyedRobots == 3) {
                    // Upgrade MadBot to RoboTank
                    outputFile << name << " has destroyed 3 robots and is upgraded to RoboTank!" << std::endl;
                    upgrade(outputFile);
                }
            }
        } else {
            // Output message if the target cell is not occupied
            outputFile << name << " fires at (" << targetX << ", " << targetY << ") but there is no target" << std::endl;
        }
    } else {
        // Output message if the target cell is not valid
        outputFile << name << " cannot fire at an invalid position (" << targetX << ", " << targetY << ")" << std::endl;
    }
    
}


void MadBot::takeAction(std::ofstream& outputFile) {
    fire(getX(), getY(), outputFile);
}

void MadBot::upgrade(std::ofstream& outputFile) {
    // Replace MadBot with RoboTank
    auto roboTank = std::make_unique<RoboTank>(getName(), getX(), getY(), battlefield);
    battlefield->replaceRobot(*this, std::move(roboTank));
    
    outputFile << "MadBot " << name << " has been upgraded to RoboTank at (" << getX() << ", " << getY() << ")" << std::endl;
}
