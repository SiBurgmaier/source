#ifndef READ_VARIABLES_H
#define READ_VARIABLES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "commonThings.h"

using json = nlohmann::json;

void replaceNewlines(std::string& variableText, const std::string& nl);
std::vector<VariableSettings> extractVariables(const std::string& filename);
void printVariables(const std::vector<VariableSettings>& variables);

#endif // READ_VARIABLES_H
