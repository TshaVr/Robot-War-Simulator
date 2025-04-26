/**********|**********|**********|
Program: Queue.h
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

#ifndef QUEUE_H
#define QUEUE_H
#include <memory>
#include "Robot.h"
// Forward declaration of Robot class
class Robot;

class Queue {
public:
    // Structure to represent a node in the queue
    struct RobotNode {
        std::unique_ptr<Robot> robot; // Unique pointer to a robot
        std::unique_ptr<RobotNode> next; // Unique pointer to the next node

        // Constructor to initialize the node with a robot
        RobotNode(std::unique_ptr<Robot> r) : robot(std::move(r)), next(nullptr) {}
    };
private:
    std::unique_ptr<RobotNode> head; // Unique pointer to the head of the queue
    RobotNode* tail; // Raw pointer to the tail of the queue
public:
    // Constructor to initialize an empty queue
    Queue() : head(nullptr), tail(nullptr) {}

    // Move constructor
    Queue(Queue&& other) noexcept 
        : head(std::move(other.head)), tail(other.tail) {
        other.tail = nullptr;
    }

    // Move assignment operator
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            head = std::move(other.head);
            tail = other.tail;
            other.tail = nullptr;
        }
        return *this;
    }

    // Method to check if the queue is empty
    bool isEmpty() const {
        return !head;
    }

    // Method to add a robot to the queue
    void enqueue(std::unique_ptr<Robot> robot) {
        auto newNode = std::make_unique<RobotNode>(std::move(robot));
        RobotNode* newTail = newNode.get();
        if (tail) {
            tail->next = std::move(newNode);
        } else {
            head = std::move(newNode);
        }
        tail = newTail;
    }

    // Method to remove and return a robot from the queue
    std::unique_ptr<Robot> dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        auto robot = std::move(head->robot);
        head = std::move(head->next);
        if (!head) {
            tail = nullptr;
        }
        return robot;
    }

    // Method to get the list of robots
    RobotNode* getRobots() const {
        return head.get();
    }

    // Destructor to clear the queue
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

#endif // QUEUE_H
