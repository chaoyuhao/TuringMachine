

#pragma once

#include "common.h"
#include "PDATrans.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


class pushdownAutomaton {
    public:
        pushdownAutomaton() 
        : program(), stack(), state(0), steps(0)
        {}
        void run();
        void loadProgram(std::string program);
        void loadStack(std::string stack);
        void reset();
        void printStack();
        void printProgram();
    private:
        std::vector<PDATransitions> program;
        std::vector<char> stack;
        int state;
        int steps;
};