#include "readVariables.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <nlohmann/json.hpp>
#include <regex>

using json = nlohmann::json;

void replaceNewlines(std::string& variableText, const std::string& nl) {
    if (nl == "DOS") {
        // Implement newline replacement with CR LF (Windows)
        variableText = std::regex_replace(variableText, std::regex("\n"), "\r\n");
    } else if (nl == "MAC" || nl == "UNIX") {
        // Implement replacing newlines with CR (Mac)
        variableText = std::regex_replace(variableText, std::regex("\r\n|\r"), "\n");
    }
}

std::vector<VariableSettings> extractVariables(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Fehler beim Öffnen der Datei." << std::endl;
        return {};
    }

    std::vector<VariableSettings> variables;
    VariableSettings currentVariable;
    std::string line;           // for reading lines from file
    bool insideStartTag = false;    // if parser is in Variable-Tags
    int defaultNameCounter = 0;
    int currentLineCount = -4; // Zählvariable für Zeilen

    while (std::getline(file, line)) {
        currentLineCount++; // Zeilenzahl erhöhen

        if (line.find("@start") == 0) {
            insideStartTag = true;
            continue;
        } else if (line.find("@end") == 0 && line.find("@endvariable") != 0) {
            if (!currentVariable.varname.empty()) {
                currentVariable.textpos = currentLineCount; // Zeilenzahl in struct speichern
                variables.push_back(currentVariable);
                currentVariable = VariableSettings();
            }
            insideStartTag = false;
            continue;
        }

        if (insideStartTag) {
            if (line.find("@variable {") == 0) {
                if (!currentVariable.varname.empty()) {
                    currentVariable.textpos = currentLineCount; // Zeilenzahl in struct speichern
                    variables.push_back(currentVariable);
                }
                currentVariable = VariableSettings();

                // Extrahiere den Inhalt zwischen den geschweiften Klammern
                size_t startPos = line.find("{");
                size_t endPos = line.find("}");
                if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                    std::string contentStr = line.substr(startPos, endPos - startPos + 1);
                    
                    json contentJson = json::parse(contentStr);

                    // Fülle die Variable entsprechend der extrahierten JSON-Daten
                    if (contentJson.contains("varname")) {
                        currentVariable.varname = contentJson["varname"].get<std::string>();
                        if (currentVariable.varname.find_first_not_of(' ') == std::string::npos) {
                            std::stringstream defaultName;
                            defaultName << "NoName" << defaultNameCounter++;
                            currentVariable.varname = defaultName.str();
                        }
                    }
                    if (contentJson.contains("seq")) {
                        currentVariable.seq = contentJson["seq"].get<std::string>();
                    }
                    if (contentJson.contains("nl")) {
                        currentVariable.nl = contentJson["nl"].get<std::string>();
                    }
                    if (contentJson.contains("addtextpos")) {
                        currentVariable.addtextpos = contentJson["addtextpos"].get<bool>();
                    }
                    if (contentJson.contains("addtextsegment")) {
                        currentVariable.addtextsegment = contentJson["addtextsegment"].get<bool>();
                    }
                    if (contentJson.contains("doxygen")) {
                        currentVariable.doxygen = contentJson["doxygen"].get<std::string>();
                    }
                }

                continue;
            }
        /**if (line.find("@endvariable") == 0) {
            if (!currentVariable.varname.empty()) {
                currentVariable.textpos = currentLineCount; // Zeilenzahl in struct speichern
                variables.push_back(currentVariable);
                currentVariable = VariableSettings();
            }
            continue;
        }*/
            // Speichere den Inhalt der Zeile in der Variable
            currentVariable.text += line;
        }
    }
    /**
    if (!currentVariable.varname.empty()) {
        currentVariable.textpos = currentLineCount; // Zeilenzahl in struct speichern
        variables.push_back(currentVariable);
    }*/

    file.close();
    for (const VariableSettings& var : variables) {
        replaceNewlines(currentVariable.text, currentVariable.nl);
    }
    return variables;
}

void printVariables(const std::vector<VariableSettings>& variables) {
    std::cout << "\n\nAnzahl Variablen: " << variables.size() << std::endl;
    std::cout << "----------------------------------" << std::endl;
    for (const VariableSettings& var : variables) {
        std::cout << "Variable: " << var.varname << std::endl;
        std::cout << "Zeile: " << var.textpos << std::endl;
        std::cout << "Seq: " << var.seq << std::endl;
        std::cout << "nl: " << var.nl << std::endl;
        std::cout << "addtextpos: " << var.addtextpos << std::endl;
        std::cout << "addtextsegment: " << var.addtextsegment << std::endl;
        std::cout << "doxygen: " << var.doxygen << std::endl;
        std::cout << "text: " << var.text << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }
}