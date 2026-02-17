#include <sstream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <iostream>



#include "helpers.hpp"
#include "utils.hpp"
#include "operator.hpp"




#define REQUIRED "required"
#define OPTIONAL "optional"

using namespace std;



vector<string> split(const string& s, char delim) {
    vector<string> tokens;
    string token;
    stringstream ss(s);

    while (getline(ss, token, delim))
        tokens.push_back(token);

    return tokens;
}

ColumnType handleColumnType(string type){
    if (type == "int"){
        return ColumnType::INT;
    }
    return ColumnType::STRING;
}

vector<FieldDefinition> parseFieldDefinitions(const string& input) {
    vector<FieldDefinition> fields;
    auto parts = split(input, ';');

    for (const auto& part : parts) {
        stringstream ss(part);
        FieldDefinition f;
        string type;
        string state;
        ss >> f.name >> type >> state;
        f.required = (state == REQUIRED);
        f.type = handleColumnType(type);
        fields.push_back(f);
    }

    return fields;
}

unordered_map<string, string> parseInsertFields(const string& input) {
    unordered_map<string, string> fields;
    auto parts = split(input, ';');

    for (const auto& part : parts) {
        auto kv = split(part, ':');
        fields[kv[0]] = kv[1];
    }

    return fields;
}


bool checkFieldNameDuplication(const vector<FieldDefinition>& fields) {
    unordered_set<string> seenNames;

    for (const auto& field : fields) {
        if (seenNames.count(field.name) > 0) {
            return true; 
        }
        seenNames.insert(field.name);
    }

    return false;
}

CompareFunction identifyOperatorSymbol(string opSymbol){
    if (opSymbol == "="){
        return equalOp;
    } else if (opSymbol == "!="){
        return notEqualOp;
    } else if (opSymbol == "<"){
        return lessThanOp;
    }
}


void printVariantValue(const Value& v) {
    visit([](const auto& value) {
        cout << value;
    }, v);
}