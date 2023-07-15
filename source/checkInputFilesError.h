#ifndef CHECKINPUTFILESERROR_H
#define CHECKINPUTFILESERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include <string>

#include "commonThings.h"

using namespace std;

void readFile(const std::string&);
int wrongFileDetector();
int checkStartAndEndErrors(); //subfunction from wrong_file_detector
int checkVariableAndEndVariableErrors();
int checkNamespaceAndCOutputFile();

#endif
