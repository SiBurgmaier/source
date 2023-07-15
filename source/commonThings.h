#ifndef COMMONTHINGS_H
#define COMMONTHINGS_H

// here are some common things that are used in the whole project

#include <stdio.h>
#include <stdlib.h>
#include <string>

struct OptionGlobalCMDLine {
    std::string inputfilename = "-1";
    std::string outputfilename = "-1";
    std::string outputtype = "-1";
    std::string headerdir = "-1";
    std::string sourcedir = "-1";
    std::string ns = "-1";
    int signperline = -1;
    int sortbyvarname = -1;
};

typedef struct {
    int signperline = -1;
    int sortbyvarname = -1;
    std::string ns = "-1";
    std::string outputfilename = "-1";
    std::string outputtype = "-1";
    std::string headerdir = "-1";
    std::string sourcedir = "-1";
} GlobalSettings;

typedef struct {
    std::string varname = "-1";
    std::string seq = "-1";
    std::string nl = "-1";
    int textpos = -1;
    bool addtextpos = false;
    bool addtextsegment = false;
    std::string doxygen = "-1";
    std::string text = "-1";
} VariableSettings;

extern GlobalSettings settings;
extern OptionGlobalCMDLine optionGlobalCMDline;
extern VariableSettings varsettings;

#endif