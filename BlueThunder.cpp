/**********|**********|**********|
Program: BlueThunder.cpp
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

#include "BlueThunder.h" 


BlueThunder::BlueThunder(std::string name, int x, int y, Battlefield* bf)
    : Robot(name, x, y, bf) ,killers(0), fireDirection(0) {}

BlueThunder::~BlueThunder() {}

void BlueThunder::look(int x, int y, std::ofstream& outputFile) {
    // BlueThunder does not look
}

void BlueThunder::move(int x, int y, std::ofstream& outputFile) {
    // BlueThunder does not move 
}

void BlueThunder::step(int x, int y, std::ofstream& outputFile) {
    // BlueThunder does not step
}

void BlueThunder::fire(int x, int y, std::ofstream& outputFile) {
    int targetX = x;
    int targetY = y;
    
    // Determine the target position based on the current fire direction (8 positions clockwise)
    switch (fireDirection) {
        case 0: targetY--; break;        // up
        case 1: targetX++; targetY--; break;  // up-right
        case 2: targetX++; break;        // right
        case 3: targetX++; targetY++; break;  // down-right
        case 4: targetY++; break;        // down
        case 5: targetX--; targetY++; break;  // down-left
        case 6: targetX--; break;        // left
        case 7: targetX--; targetY--; break;  // up-left
    }

      outputFile << name << " fires at (" << targetX << ", " << targetY << ")\n";
    
    if (battlefield->isValidPosition(targetX, targetY)) {
        if (battlefield->isOccupied(targetX, targetY)) {
            Robot* target = battlefield->getRobotAt(targetX, targetY);
            if (target) { // Check if target is valid
            target->decrementLives();
            outputFile << name << " hits " << target->getName() << std::endl;
            
            if (!target->isAlive()) {
                outputFile << target->getName() << " has been destroyed!" << std::endl;
                battlefield->removeRobot(targetX, targetY);
                killers++;
                if (killers == 3) {
                    outputFile << name << " has destroyed 3 robots and is upgraded!" << std::endl;
                    upgrade(outputFile);
                }
              }
            }
        } else {
            outputFile << "But there is no target at (" << targetX << ", " << targetY << ")" << std::endl;
        }
    } else {
        outputFile << name << " cannot fire at an invalid position (" << targetX << ", " << targetY << ")" << std::endl;
    }

    fireDirection = (fireDirection + 1) % 8;  // Update fire direction to next clockwise position
}

void BlueThunder::takeAction(ofstream& outputFile){
    
     fire(positionX, positionY, outputFile);
    
}
void BlueThunder::upgrade(std::ofstream& outputFile) {
    // Replace BlueThunder with MadBot
    auto madBot = std::make_unique<MadBot>(getName(), getX(), getY(), battlefield);
    battlefield->replaceRobot(*this, std::move(madBot));
    
    outputFile << "BlueThunder " << name << " has been upgraded to MadBot at (" << getX() << ", " << getY() << ")" << std::endl;
   }

