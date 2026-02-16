#ifndef HELPERS_H
#define HELPERS_H


#include <string>
#include <vector>
#include <unordered_map>


#include "utils.hpp"

using namespace std;

vector<string> split(const string& s, char delim);

vector<FieldDefinition> parseFieldDefinitions(const string& input);

unordered_map<string, string> parseInsertFields(const string& input);

Condition parseCondition(stringstream& ss);

bool checkFieldNameDuplication(const vector<FieldDefinition>& fields);

ColumnType handleColumnType(string type);


#endif // HELPERS_H