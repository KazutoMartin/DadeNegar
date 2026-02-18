#ifndef UTILS_H
#define UTILS_H

#include "enums.hpp"
#include <string>

struct FieldDefinition {
    std::string name;
    ColumnType type;
    bool required;
};


#endif // UTILS_H