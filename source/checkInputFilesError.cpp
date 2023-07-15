#include "checkInputFilesError.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

std::string fileContent;    //TODO: now it reads the file 2 time (readFile() and search_global()). We need both for different functions. But the code doesnt need to be efficient. So we can leave it like this for now.

void readFile(const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string tempContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        fileContent = tempContent;

        file.close();
    } else {
        std::cout << "Error opening the file." << std::endl;
    }
}

int wrongFileDetector() {
    // Returns 1 if something went wrong with the file.
    // Checks the following cases:
    // - If there is an insufficient number of @start and @end
    // - If @variable and @endvariable are nested or if there is one too few
    // - If there is a namespace specified while the output file is a C file (can only be done once Jannik and David have globally read it!)

    if (checkStartAndEndErrors()) {
        // Output specialized to the errors
        return 1;
    }

    if (checkVariableAndEndVariableErrors()) {
        // Output specialized to the errors
        return 1;
    }

    if (checkNamespaceAndCOutputFile()) {
        // Output specialized to the errors
        return 1;
    }

    return 0;
}

int checkStartAndEndErrors() {

    bool hasEnd = false, hasStart = false;
    int16_t found = -1;
    uint16_t icounter = 0;

    // Check if there are a different number of @start and @end
    if (fileContent.find("\n@end\n") != string::npos) hasEnd = true;    //TODO: doesn't work if @end is the last line and @start in first line
    if (fileContent.find("\n@start\n") != string::npos) hasStart = true;

    if (hasEnd != hasStart) {  // There is an @start but no @end, or vice versa
        cout << "There is an @start but no @end, or vice versa. This is not allowed.\n";
        return 1;
    }
    // End of check for a different number of @start and @end

    // Check for multiple @start or @end
    do {
        found = fileContent.find("\n@start\n", found + 1);
        icounter++;
    } while (found != -1);

    if (icounter > 2) {
       

 cout << "There are multiple @start in the input file. This is not allowed.\n";
        return 1;
    }

    found = -1;
    icounter = 0;
    do {
        found = fileContent.find("\n@end\n", found + 1);
        icounter++;
    } while (found != -1);

    if (icounter > 2) {
        cout << "There are multiple @end in the input file. This is not allowed.\n";
        return 1;
    }
    // End of check for multiple @start or @end

    //@end before @start
    if (fileContent.find("\n@start\n") > fileContent.find("\n@end\n")) {
        cout << "There is an @end before an @start. This is not allowed.\n";
        return 1;
    }
    // End of check for @end before @start

    return 0;
}

int checkVariableAndEndVariableErrors() {

    int16_t found = -1;
    int16_t tmp = 0; // Used because found is set to -1 on the last iteration, but it is needed to check if there is another @endvariable.
    int16_t to_test_found_var_before_endvar = 0; // Used to check if there is a @variable before the first @endvariable.

    if (fileContent.find("\n@variable") != string::npos && fileContent.find("\n@endvariable\n") != string::npos) {   // Only check for problems if @variable and @endvariable are present.
        // Check for @endvariable before @variable
        if (fileContent.find("\n@variable") > fileContent.find("\n@endvariable\n")) {
            cout << "There is an @endvariable before @variable was found!\n";
            return 1;
        }
        // End of check for @endvariable before @variable

        do {
            found = fileContent.find("\n@variable", found + 1);

            if (found != string::npos) {

                // Check for @variable before @endvariable after there has already been a @variable
                to_test_found_var_before_endvar = found;
                found = fileContent.find("\n@endvariable\n", found + 1);   // Find the next @endvariable and update found
                if (found > fileContent.find("\n@variable", to_test_found_var_before_endvar + 1)) {
                    cout << "There is a @variable before @endvariable was expected!\n";
                    return 1;
                }
                // End of this check

                // Check for two consecutive @endvariable
                if (fileContent.find("\n@endvariable\n", found + 1) < fileContent.find("\n@variable", found + 1)) {
                    cout << "There is an @endvariable before @variable was expected!\n";
                    return 1;
                }
                // End of this check

                // Check if the @endvariable is missing at the end, but I'm not entirely sure anymore. It works though.
                tmp = found;
                if (found == string::npos) {
                    cout << "\nThere is a @variable but no @endvariable.\n";
                    return 1;
                }
            }
            else {
                if (fileContent.find("\n@endvariable\n", tmp + 1) != string::npos) {
                    found = fileContent.find("\n@endvariable\n", found + 1);
                    cout << "\nThere is an @endvariable but no @variable.\n";
                    return 1;
                }
            }

        } while (found != -1

);
    }

    return 0;
}

int checkNamespaceAndCOutputFile() {
    if(optionGlobalCMDline.outputtype == "C" && optionGlobalCMDline.ns != "-1") {
        std::cout << "A \"namespace\" was specified even though the output file is a C file. This is not possible!" << std::endl;
        return 1;
    }

    return 0;
}