#ifndef ENUMS_H
#define ENUMS_H

#include <string>
#include <vector>
#include <unordered_map>

enum class ColumnType {
    INT,
    STRING
};

enum class CommandType {
    CREATE_TABLE,
    CREATE_ENHANCED_TABLE,
    DROP_TABLE,
    INSERT,
    UPDATE,
    SELECT
};


#endif //ENUMS_H