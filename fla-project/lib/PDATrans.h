
#pragma once

#include "common.h"
#include <iostream>
#include <string>
#include <vector>

class PDATransitions {
public:
    PDATransitions() 
        : state(0), stackRead(""), stackWrite(""), nextState(0)
    {}
    
    PDATransitions(int state, std::string stackRead, std::string stackWrite, int nextState)
        : state(state), stackRead(stackRead), stackWrite(stackWrite), nextState(nextState)
    {}

    // Getters
    int getState() const { return state; }
    std::string getStackRead() const { return stackRead; }
    std::string getStackWrite() const { return stackWrite; }
    int getNextState() const { return nextState; }

    void toString() const {
        std::cout << '(' << state << "," << stackRead << ") -> (" << stackWrite << "," << nextState << ')' << std::endl;
    }
    
private:
    int state;
    std::string stackRead;
    std::string stackWrite;
    int nextState;
};
