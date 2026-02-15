#ifndef UTILS_H
#define UTILS_H

#include "enums.hpp"
#include <string>

struct FieldDefinition {
    std::string name;
    ColumnType type;
    bool required;
};

struct InsertField {
    std::string name;
    std::string value;
};

struct Condition {
    std::string field;
    std::string op;
    std::string value;
};

#endif // UTILS_H