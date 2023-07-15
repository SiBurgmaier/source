// g++ main.cpp source\readConsolInput.cpp source\readVariables.cpp source\checkInputFilesError.cpp source\readAndCompareOptions.cpp source\CTextToCPP.cpp -o main.exe -I.\CMakeFiles\includes\rapidjson-master\include
// ./main.exe beispiel.txt

// you can also execute mingw32-make in the subfolder CMakeFiles

//Program design C/C++ 2023
//Silas Burgmaier, Ben Felber, Jannik Dangel, David Oswald (TIT22)
//Code generator GenTxtSrcCode

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include "getopt.h" //VSCode may throw an error because the compiler doesn't recognize it. However, it works when compiling with g++.
#include "source/checkInputFilesError.h"
#include "source/readConsolInput.h"
#include "source/readAndCompareOptions.h"
#include "source/commonThings.h"
#include "source/CTextToCPP.h"
#include "source/readVariables.h"

using namespace std;    //for readability and overview we use std::cout instead of cout

OptionGlobalCMDLine optionGlobalCMDline; // Global variable for the command line options
GlobalSettings settings; // Global variable for the settings from the input file
VariableSettings varsettings; // Global variable for the variable settings from the input file

int main(int argc, char* argv[]) {
    	
    if (parameterParsing(argc, argv)) { // Function is executed here and immediately checked if everything worked.
        return 1; // Program terminates
    }
    std::vector<std::string> filenamens = splitString(optionGlobalCMDline.inputfilename, "\n");

    for (int i = 0; i <= filenamens.size(); i++) {

        readFile(filenamens[i]);
        search_global(filenamens[i]);
        compareAndChangeOptionGlobalCMDline(&settings, &optionGlobalCMDline);  //settings are the infos from the input file and the optionGlobalCMDline are the infos from the command line
        printOptionGlobalCMDLine(optionGlobalCMDline);  //can be deleted. only for testen and overview

        if (wrongFileDetector()) {
            return 1; // Program terminates
        }

        std::vector<VariableSettings> variables = extractVariables(filenamens[i]);
        int lenght = variables.size();
        printVariables(variables); //can be deleted. only for testen and overview
        CTextToCPP *first = CTextToCPP::create(variables[1]);
        if (first == nullptr){
            return 1;
        }

        for (int i = 2; i < lenght; i++) {
        CTextToCPP *newVar = CTextToCPP::create(variables[i]); //TODO: die +1 is schwierig aber notwendig
        (*first).addElement(newVar);
        }

        if(optionGlobalCMDline.sortbyvarname == 1) {
            (*first).sort(&first);
        }

        (*first).writeDeclaration(settings);
        (*first).writeImplementation(settings);
        (*first).clear();
    }

    cout << "Programm beendet" << endl;
    cout << "\n\n\nSomething changed\n\n\n" << endl;

    return 0;
}