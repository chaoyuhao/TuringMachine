
#include <iostream>

#include "common.h"
#include "TMParser.h"
#include "TMSim.h"
#include "PDASim.h"

#define GREEN(x) "\033[32m" << x << "\033[0m"
#define RED(x) "\033[31m" << x << "\033[0m"

using namespace std;

int main(int argc, char* argv[]){
    
    cout << "hello" << endl;

    if(argc == 1){
        return 1;
    }

    cout << GREEN("Hello FLA Project!") << endl;

    cout << "Arguments: " << argv[0] << endl;
    cout << "Arguments: " << argv[1] << endl;
    cout << "Arguments: " << argv[2] << endl;

    string programFile = argv[1];
    
    if (programFile.size() >= 3 && programFile.substr(programFile.size() - 3) == ".tm" ) {
        cout << GREEN("Turing Machine Mode Format") << endl;
        
        TMParser parser;
        
        parser.parseTMFile(programFile, false);

    }else if (programFile.size() >= 3 && programFile.substr(programFile.size() - 4) == ".pda"){

        cout << GREEN("Pushdown Automaton Format") << endl;


    }else {
        cout << RED("Invalid file format !\n Only accept input file end with .tm or .pda") << endl;
    }

    return 0;
}