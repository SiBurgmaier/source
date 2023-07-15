#include "readAndCompareOptions.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

int compareAndChangeOptionGlobalCMDline(const GlobalSettings* settings, OptionGlobalCMDLine* options) { //settings are the settings from the file, options are the settings from the command line
    if (options->outputfilename == "-1") {  // If the user didn't specify an outputfilename, use the one from the settings file. -1 are the default values.
        options->outputfilename = settings->outputfilename;
    }
    if (options->outputtype == "-1") {  // same as above
        options->outputtype = settings->outputtype;
    }
    if (options->headerdir == "-1") {
        options->headerdir = settings->headerdir;
    }
    if (options->sourcedir == "-1") {
        options->sourcedir = settings->sourcedir;
    }
    if (options->ns == "-1") {
        options->ns = settings->ns;
    }
    if (options->signperline == -1) {
        options->signperline = settings->signperline;
    }
    if (options->sortbyvarname == -1) {
        options->sortbyvarname = settings->sortbyvarname;
    }
    return 0;
}

std::vector<std::string> splitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    std::string::size_type pos = 0;
    std::string::size_type start = 0;

    while ((pos = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, pos - start));
        start = pos + delimiter.length();
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

void search_global(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error when opening the file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("@global") != std::string::npos) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, '{'); // extract the part before the first element of the block global { ... }
            if (!std::getline(iss, token, '}')) continue; // skip the block if the first element is emty

            std::istringstream blockStream(token);
            std::string element;
            while (std::getline(blockStream, element, ',')) {
                std::istringstream elementStream(element);
                std::string key, value;
                if (std::getline(elementStream, key, ':') && std::getline(elementStream, value)) {
                    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
                    value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
                    if (key.front() == '\"' && key.back() == '\"')
                        key = key.substr(1, key.length() - 2);
                    if (value.front() == '\"' && value.back() == '\"')
                        value = value.substr(1, value.length() - 2);

                    if (key == "signperline")
                        settings.signperline = std::stoi(value);
                    else if (key == "sortbyvarname")
                        settings.sortbyvarname = (value == "false") ? 0 : 1;    // 0 = false, 1 = true //short form if else
                    else if (key == "namespace") 
                        settings.ns = value;
                    else if (key == "outputfilename")
                        settings.outputfilename = value;
                    else if (key == "outputtype")
                        settings.outputtype = value;
                    else if (key == "headerdir")
                        settings.headerdir = value;
                    else if (key == "sourcedir")
                        settings.sourcedir = value;
                }
            }
        }
    }

    file.close();
}

void printGlobalSettings(const GlobalSettings& settings) {
    std::cout << "signperline: " << settings.signperline << std::endl;
    std::cout << "sortbyvarname: " << (settings.sortbyvarname ? "true" : "false") << std::endl;
    std::cout << "ns: " << settings.ns << std::endl;
    std::cout << "outputfilename: " << settings.outputfilename << std::endl;
    std::cout << "outputtype: " << settings.outputtype << std::endl;
    std::cout << "headerdir: " << settings.headerdir << std::endl;
    std::cout << "sourcedir: " << settings.sourcedir << std::endl;
}

void printOptionGlobalCMDLine(const OptionGlobalCMDLine& options) {
    std::cout << "Input Filename: " << options.inputfilename << std::endl;
    std::cout << "Output Filename: " << options.outputfilename << std::endl;
    std::cout << "Output Type: " << options.outputtype << std::endl;
    std::cout << "Header Directory: " << options.headerdir << std::endl;
    std::cout << "Source Directory: " << options.sourcedir << std::endl;
    std::cout << "Namespace: " << options.ns << std::endl;
    std::cout << "Sign per Line: " << options.signperline << std::endl;
    std::cout << "Sort by Variable Name: " << options.sortbyvarname << std::endl;
}
