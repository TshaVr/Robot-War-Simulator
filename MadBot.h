/**********|**********|**********|
Program: MadBot.h
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

#ifndef MADBOT_H
#define MADBOT_H

#include <memory> // For std::unique_ptr and std::make_unique
#include <string> 
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()  
#include <memory>     
#include "Battlefield.h" 
#include "Robot.h"  // Assuming "robots" is a header file
#include "RoboTank.h"



class MadBot :  public virtual Robot {
private:
    int destroyedRobots = 0;

public:
    MadBot(std::string name, int x, int y, Battlefield* bf);
    ~MadBot() ;
    void look(int x, int y, std::ofstream& outputFile) ;
    void move(int x, int y, std::ofstream& outputFile) ;
    void fire(int x, int y, std::ofstream& outputFile) ;
    void step(int x, int y, std::ofstream& outputFile) ;
    void upgrade(std::ofstream& outputFile);
    void takeAction(std::ofstream& outputFile) ;
};
#endif 