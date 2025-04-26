/**********|**********|**********|
Program: RoboCop.h
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

#ifndef ROBOCOP_H
#define ROBOCOP_H

#include <memory>           // For std::unique_ptr and std::make_unique
#include <string>           // For std::string
#include <iostream>         // For std::cout and std::cerr
#include <fstream>          // For std::ofstream
#include <cstdlib>          // For rand()
#include <ctime>            // For time()
#include "Battlefield.h"    // Include the Battlefield header
#include "Robot.h"          // Include the Robot header (base class)


class TerminatorRoboCop; // Forward declaration

/*
 RoboCop: Each turn, this robot scans its surroundings, moves once, and fires three times
 at random positions within a city block distance of 10 units. It cannot move to occupied
 locations. After destroying 3 robots, it upgrades to TerminatorRoboCop, allowing it to
 step on and destroy other robots.
 */

class RoboCop : public virtual Robot {
protected:
    int killers;       
public:
    RoboCop(std::string name, int x, int y, Battlefield* bf);
    ~RoboCop() ; // Destructor declaration
    void look(int x, int y, std::ofstream& outputFile) ;
    void move(int x, int y, std::ofstream& outputFile) ;
    void fire(int x, int y, std::ofstream& outputFile) ;
    void step(int x, int y, std::ofstream& outputFile) ;
    void takeAction(std::ofstream& outputFile) ;
    void upgrade(std::ofstream& outputFile) ;
};
#endif 
