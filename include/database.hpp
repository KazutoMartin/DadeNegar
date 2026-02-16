#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "table.hpp"
#include "helpers.hpp"

using namespace std;


class Database {
private:
    unordered_map<string, shared_ptr<BaseTable>> tables_;

public:
    Database() = default;

    shared_ptr<BaseTable> getTable(const string& tableName) const;

    void createTable(string tableName, vector<FieldDefinition> fields);
    void createEnhancedTable(string tableName, vector<FieldDefinition> fields);
    void dropTable(string tableName);
    void insert(string tableName, unordered_map<string, string> fields);


};

#endif //DATABASE_H