
#pragma once
#include "common.h"
#include "TMSim.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

class TMParser {
public:
    TMParser() : _verbose(false), tm() {}

    void parseTMFile(const std::string &filename, bool verbose);

    std::shared_ptr<TuringMachine> getTM() {
        return tm;
    }

private:
    bool _verbose;
    std::shared_ptr<TuringMachine> tm;

    // TM = (Q, Σ, Γ, δ, q0, B, F)
    void getQ(std::string s);
    void getSigma(std::string s);
    void getGamma(std::string s);
    void getDelta(std::string s);
    void getQ0(std::string s);
    void getB(std::string s);
    void getF(std::string s);
    void getN(std::string s);
    
    // Check if the character is invalid
    const char invalidSigma[7] = {' ', ',', ';', '{', '}', '*', '_'};
    const char invalidGamma[6] = {' ', ',', ';', '{', '}', '*'};

};