

#include "common.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <memory>

#include "TMSim.h"
#include "TMParser.h"

using namespace std;

static inline void show_syntax_error(const string& line) {
    throw runtime_error("Error in Turing machine parser: " + line);
}

static vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void TMParser::getQ(string s) {
    //format
    //#Q = {q0,q1,...,qn}
    if (s[0] != '{' || s[s.size() - 1] != '}') {
        throw runtime_error("Error in Turing machine parser (missing brankets): " + s);
    }
    vector<string> states = split(s.substr(1, s.size() - 2), ',');
    for (const auto& state : states) {
        tm->getConfiguration().addState(state);
    }
}

void TMParser::getSigma(string s) {
    //format
    //#Σ = {a, b, ..., z}
    if (s[0] != '{' || s[s.size() - 1] != '}') { throw runtime_error("Error in Turing machine parser (missing brankets): " + s); }
    vector<string> inputs = split(s.substr(1, s.size() - 2), ',');
    for (const auto& input : inputs) {
        tm->getConfiguration().addInputAlphabet(input[0]);
    }
}

void TMParser::getGamma(string s) {
    if (s[0] != '{' || s[s.size() - 1] != '}') { throw runtime_error("Error in Turing machine parser (missing brankets): " + s); }
    vector<string> inputs = split(s.substr(1, s.size() - 2), ',');
    for (const auto& input : inputs) {
        tm->getConfiguration().addTapeAlphabet(input[0]);
    }
}

void TMParser::getQ0(string s) {
    tm->getConfiguration().setStartState(s);
}

void TMParser::getB(string s) {
    if (s.size() != 1) { throw runtime_error("Error in Turing machine parser (invalid blank symbol): " + s); }
    tm->getConfiguration().setBlankSymbol(s[0]);
}

void TMParser::getF(string s) {
    if (s[0] != '{' || s[s.size() - 1] != '}') { throw runtime_error("Error in Turing machine parser (missing brankets): " + s); }
    vector<string> inputs = split(s.substr(1, s.size() - 2), ',');
    for (const auto& input : inputs) {
        tm->getConfiguration().addAcceptState(input);
    }
}

void TMParser::getN(string s) {
    int n = stoi(s);
    tm->getConfiguration().setNumTapes(n);
}

void TMParser::parseTMFile(const std::string& filename, bool verbose) {
    
    _verbose = verbose;
    tm = make_shared<TuringMachine>();

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    vector<TMTransitions> program;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == ';') {
            continue;
        }

        istringstream iss(line);
        string def, eq, content;
        iss >> def;
        if(def[0] == '#'){
            iss >> eq >> content;
            if(eq != "=") show_syntax_error(line);
            
            if(def == "#Q") getQ(content);
            else if(def == "#S") getSigma(content);
            else if(def == "#G") getGamma(content);
            else if(def == "#q0") getQ0(content);
            else if(def == "#B") getB(content);
            else if(def == "#F") getF(content);
            else if(def == "#N") getN(content);
            else show_syntax_error(line);

        }else { // transitions
            // check if state is valid
            if (tm->getConfiguration().containsState(def)) {
                
                // parse the transition
                string state, input, output, move, new_state;
                state = def;
                iss >> input >> output >> move >> new_state;
                if (move.size() != 1) {
                    throw runtime_error("Error in Turing machine parser (invalid move direction): " + line);
                }
                for (int i=0; i<tm->getNumTapes(); i++) {
                    program.emplace_back(state, input[i], output[i], move[i], new_state);
                }
            } else {
                throw runtime_error("Error in Turing machine parser (invalid state): " + def);
            }

        }
    }

    file.close();
    cout << "Parsed Turing Machine Completed" << endl;

}