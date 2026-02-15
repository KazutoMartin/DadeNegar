#ifndef HELPERS_H
#define HELPERS_H


#include <string>
#include <vector>

#include "utils.hpp"



std::vector<std::string> split(const std::string& s, char delim);

std::vector<FieldDefinition> parseFieldDefinitions(const std::string& input);

std::vector<InsertField> parseInsertFields(const std::string& input);

Condition parseCondition(std::stringstream& ss);

bool checkFieldNameDuplication(const std::vector<FieldDefinition>& fields);

ColumnType handleColumnType(std::string type);


#endif // HELPERS_H