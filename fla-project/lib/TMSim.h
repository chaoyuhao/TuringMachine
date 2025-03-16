

#pragma once

#include "common.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>
#include <set>

class TMTransitions {
public:
    TMTransitions() 
        : state(0), read(' '), write(' '), move(static_cast<char>(Direction::STAY)), nextState(0)
    {}
    
    TMTransitions(std::string state, char read, char write, char move, std::string nextState)
        : state(state), read(read), write(write), move(move), nextState(nextState)
    {
        validateMove(move);
    }

    // Getters
    std::string getState() const { return state; }
    char getRead() const { return read; }
    char getWrite() const { return write; }
    char getMove() const { return move; }
    std::string getNextState() const { return nextState; }

    void toString() const {
        std::cout << '(' << state << "," << read << ") -> (" << write << "," << move << "," << nextState << ')' << std::endl;
    }

private:
    std::string state;
    char read;
    char write;
    char move;
    std::string nextState;

    void validateMove(char m) {
        if (m != 'L' && m != 'R' && m != 'S') {
            throw std::invalid_argument("Invalid move direction");
        }
    }
};

class TMConfiguration {

public:

    void addState(const std::string& state) {
        states.insert(state);
    }
    void addInputAlphabet(char input) {
        inputAlphabet.insert(input);
    }
    void addTapeAlphabet(char tape) {
        tapeAlphabet.insert(tape);
    }
    void setStartState(const std::string& state) {
        startState = state;
    }
    void setBlankSymbol(char blank) {
        blankSymbol = blank;
    }
    void addAcceptState(const std::string& state) {
        acceptStates.insert(state);
    }
    void addTransition(const TMTransitions& transition) {
        transitions.push_back(transition);
    }
    void setNumTapes(int n) {
        numTapes = n;
    }

    int getNumTapes() const { return numTapes; }

    bool containsState(const std::string& state) {
        if (states.find(state) == states.end()) {
            throw std::invalid_argument("State not found");
        }
        else return true;
    }

private:
    std::set<std::string> states;        // Q
    std::set<char> inputAlphabet;        // Σ
    std::set<char> tapeAlphabet;         // Γ
    std::string startState;              // q0
    char blankSymbol;                    // B
    std::set<std::string> acceptStates;  // F
    std::vector<TMTransitions> transitions; // δ
    int numTapes;                        // N
};

class TuringMachine {
public:
    TuringMachine() 
        : program(), tapes(), heads(), state(0), steps(0), isHalted(false), stateManager(), config()
    {}

    // Public methods
    void run();
    void loadProgram(const std::vector<TMTransitions>& program);
    void loadTape(const std::string& tape);
    void reset();
    void printTape() const;
    void printProgram() const;

    // Getters
    bool isFinished() const { return isHalted; }
    int getSteps() const { return steps; }
    int getCurrentState() const { return state; }
    StateManager getStateManager() const { return stateManager; }
    TMConfiguration getConfiguration() const { return config; }
    int getNumTapes() const { return config.getNumTapes(); }
    
    // Optional: get current tape content
    std::string getTapeContent() const;

private:
    std::vector<TMTransitions> program;  // Changed from string to TMInst
    std::vector<std::vector<char>> tapes;
    std::vector<int> heads;
    int state;
    int steps;
    bool isHalted;
    StateManager stateManager;
    TMConfiguration config;

    // Private helper methods
    void step();
    void execute(const TMTransitions& instruction);
    void move(Direction direction);
    void printTuringMachine() const;
    void ensureTapeCapacity(int position);

    // Constants
    static const char BLANK = '_';
    static const int TAPE_EXTENSION_SIZE = 100;
};

