#ifndef CTEXTTOCPP_H
#define CTEXTTOCPP_H

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "commonThings.h"

class CTextToCPP {
private:
    CTextToCPP* next = nullptr;
    VariableSettings varsettings;

public:
    CTextToCPP(VariableSettings& varsettings);
    virtual ~CTextToCPP();

    static CTextToCPP *create(VariableSettings &varsettings);
    virtual std::string getdoxygen();
    std::string getvarname();
    bool getAddTextpos();
    int getTextpos();
    std::string getText();
    void addElement(CTextToCPP* obj);
    void writeDeclaration(GlobalSettings& settings);
    void writeImplementation(GlobalSettings& settings);
    void clear();
    std::string getVariableName();
    CTextToCPP* getNext();
    void sort(CTextToCPP** first);

    virtual std::string convertText(char text);
    virtual void writeImplementationSub(std::ofstream& file, GlobalSettings& settings);
    virtual std::string declaration();
    virtual std::string definition();
    std::string writeTextsegment();
    std::string toUpper(std::string text);
};

// CTextToEscSeq child class
class CTextToEscSeq : public CTextToCPP {
public:
    CTextToEscSeq(VariableSettings& varsettings);
    virtual void writeImplementationSub(std::ofstream& file, GlobalSettings& settings) override;
};

// CTextToOctSeq child class
class CTextToOctSeq : public CTextToCPP {
public:
    CTextToOctSeq(VariableSettings& varsettings);
    virtual void writeImplementationSub(std::ofstream& file, GlobalSettings& settings) override;
    virtual std::string convertText(char text) override;
};

// CTextToHexSeq child class
class CTextToHexSeq : public CTextToCPP {
public:
    CTextToHexSeq(VariableSettings& varsettings);
    virtual void writeImplementationSub(std::ofstream& file, GlobalSettings& settings) override;
    virtual std::string convertText(char text) override;
};

// CTextToRawHexSeq child class
class CTextToRawHexSeq : public CTextToCPP {
public:
    CTextToRawHexSeq(VariableSettings& varsettings);
    virtual void writeImplementationSub(std::ofstream& file, GlobalSettings& settings) override;
    virtual std::string convertText(char text) override;
    virtual std::string declaration() override;
    virtual std::string definition() override;
};

#endif // HEADER_H