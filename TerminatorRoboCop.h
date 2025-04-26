/**********|**********|**********|
Program: TerminatorRoboCop.h
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

#ifndef TERMINATORROBOCOP_H
#define TERMINATORROBOCOP_H

#include <memory> // For std::unique_ptr and std::make_unique
#include <string>   
#include <fstream>      
#include "RoboCop.h"
#include "Terminator.h"
#include "Battlefield.h" 

class UltimateRobot; // Forward declaration

class TerminatorRoboCop : public virtual RoboCop, public virtual Terminator {
protected:
   int killers;
public:
     TerminatorRoboCop(std::string name, int x, int y, Battlefield* bf);
      virtual ~TerminatorRoboCop();
      void look(int x, int y, std::ofstream& outputFile) ;
      void move(int x, int y, std::ofstream& outputFile) ;
      void fire(int x, int y, std::ofstream& outputFile) ;
      void takeAction(std::ofstream& outputFile) ;
      void step(int x, int y, std::ofstream& outputFile);
      void upgrade(std::ofstream& outputFile) ;
};

#endif 