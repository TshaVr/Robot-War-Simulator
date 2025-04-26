/**********|**********|**********|
Program: UltimateRobot.h
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

#ifndef ULTIMATEROBOT_H
#define ULTIMATEROBOT_H

#include <memory>       // For std::unique_ptr
#include <string>
#include <fstream>  
#include <cstdlib>      // For std::rand()
#include <ctime>        // For std::time()
#include "TerminatorRoboCop.h"
#include "Battlefield.h"

/*This robot moves like the TerminatorRoboCop, stepping and
killing any robots on its path. In each turn, this robot shoots
randomly at 3 locations in the battlefield*/

class UltimateRobot : public TerminatorRoboCop {
private:
    int killers;
public:
    UltimateRobot(std::string name, int x, int y, Battlefield* bf);
    virtual ~UltimateRobot(); 
    void look(int x, int y, std::ofstream& outputFile) ;
    void move(int x, int y, std::ofstream& outputFile) ;
    void step(int x, int y, std::ofstream& outputFile) ;
    void fire(int x, int y, std::ofstream& outputFile) ;
    void takeAction(std::ofstream& outputFile) ;
};

#endif 