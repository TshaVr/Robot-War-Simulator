/**********|**********|**********|
Program: Robot.h
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

#ifndef ROBOT_H
#define ROBOT_H

#include <memory>       // For std::unique_ptr
#include <string>       // For std::string
#include <fstream>      // For std::ofstream
#include <iostream>
#include "Battlefield.h" 

class Battlefield;  // Forward declaration

// Abstract base class for robots in a battlefield simulation.
// Defines common attributes and pure virtual functions for robot actions

class Robot {
protected:
    std::string name;
    int positionX, positionY;
    int lives;
    Battlefield* battlefield;
    
public: 
    Robot(std::string name, int x, int y, Battlefield* bf)
        : name(name), positionX(x), positionY(y), lives(3), battlefield(bf) {}
    
    virtual void look(int x, int y, std::ofstream& outputFile) = 0;
    virtual void move(int x, int y, std::ofstream& outputFile) = 0;
    virtual void fire(int x, int y, std::ofstream& outputFile) = 0;
    virtual void step(int x, int y, std::ofstream& outputFile) = 0;
    virtual void takeAction(std::ofstream& outputFile) = 0; 
    virtual void upgrade(std::ofstream& outputFile) = 0;
    virtual ~Robot() {}

    bool isAlive() const { return lives > 0; }
    void decrementLives() { lives--; }
    std::string getName() const { return name; }
    void setX(int x) { positionX = x; }
    void setY(int y) { positionY = y; }
    int getX() const { return positionX; }
    int getY() const { return positionY; }
    int getLives() const { return lives; }
};

// Abstract Subclasses

class MovingRobot : virtual public Robot {
public:
    MovingRobot(const std::string& name, int x, int y,  Battlefield* bf)
        : Robot(name, x, y, bf) {}

    virtual void move(int x, int y, std::ofstream& outputFile)  = 0;
};

class ShootingRobot : virtual public Robot {
public:
    ShootingRobot(const std::string& name, int x, int y,  Battlefield* bf)
        : Robot(name, x, y, bf) {}

    virtual void fire(int x, int y, std::ofstream& outputFile)  = 0;
};

class SeeingRobot : virtual public Robot {
public:
    SeeingRobot(const std::string& name, int x, int y,  Battlefield* bf)
        : Robot(name, x, y, bf) {}

    virtual void look(int x, int y, std::ofstream& outputFile)  = 0;
};

class SteppingRobot : virtual public Robot {
public:
    SteppingRobot(const std::string& name, int x, int y,  Battlefield* bf)
        : Robot(name, x, y, bf) {}

    virtual void step(int x, int y, std::ofstream& outputFile)  = 0;
};

#endif // ROBOT_H