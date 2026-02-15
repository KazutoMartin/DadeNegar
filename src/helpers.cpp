#include <sstream>
#include <vector>
#include <memory>
#include <unordered_set>

#include "helpers.hpp"
#include "utils.hpp"


std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);

    while (std::getline(ss, token, delim))
        tokens.push_back(token);

    return tokens;
}

ColumnType handleColumnType(std::string type){
    if (type == "int"){
        return ColumnType::INT;
    }
    return ColumnType::STRING;
}

std::vector<FieldDefinition> parseFieldDefinitions(const std::string& input) {
    std::vector<FieldDefinition> fields;
    auto parts = split(input, ';');

    for (const auto& part : parts) {
        std::stringstream ss(part);
        FieldDefinition f;
        std::string type;
        ss >> f.name >> type >> f.required;
        f.type = handleColumnType(type);
        fields.push_back(f);
    }

    return fields;
}

std::vector<InsertField> parseInsertFields(const std::string& input) {
    std::vector<InsertField> fields;
    auto parts = split(input, ';');

    for (const auto& part : parts) {
        auto kv = split(part, ':');
        fields.push_back({kv[0], kv[1]});
    }

    return fields;
}

Condition parseCondition(std::stringstream& ss) {
    Condition cond;
    ss >> cond.field >> cond.op >> cond.value;
    return cond;
}

bool checkFieldNameDuplication(const std::vector<FieldDefinition>& fields) {
    std::unordered_set<std::string> seenNames;

    for (const auto& field : fields) {
        if (seenNames.count(field.name) > 0) {
            return true; 
        }
        seenNames.insert(field.name);
    }

    return false;
}

