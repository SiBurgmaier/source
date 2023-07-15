#ifndef READANDCOMPAREOPTIONS_H
#define READANDCOMPAREOPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>

#include "commonThings.h"

using namespace std;

std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);
int compareAndChangeOptionGlobalCMDline(const GlobalSettings* , OptionGlobalCMDLine*);
void search_global(const std::string&);
void printGlobalSettings(const GlobalSettings&);
void printOptionGlobalCMDLine(const OptionGlobalCMDLine&);


#endif
