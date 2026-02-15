#ifndef COMMANDS_H
#define COMMANDS_H

#include "enums.hpp"
#include "utils.hpp"
#include "database.hpp"

#include <iostream>


class Database; 


class Command {
public:
    virtual ~Command() = default;

    virtual void execute(Database& db) = 0;
};

class CreateTableCommand : public Command {
private:
    std::string tableName_;
    std::vector<FieldDefinition> fields_;

public:
    CreateTableCommand(std::string tableName,
                       std::vector<FieldDefinition> fields
                    )
        : tableName_(std::move(tableName)),
          fields_(std::move(fields)) {}

    void execute(Database& db) override {
            db.createTable(tableName_, fields_);
    }
};

class CreateEnhancedTableCommand : public Command {
private:
    std::string tableName_;
    std::vector<FieldDefinition> fields_;

public:
    CreateEnhancedTableCommand(std::string tableName,
                       std::vector<FieldDefinition> fields
                    )
        : tableName_(std::move(tableName)),
          fields_(std::move(fields)) {}

    void execute(Database& db) override {
            db.createEnhancedTable(tableName_, fields_);
    }
};


class DropTableCommand : public Command {
private:
    std::string tableName_;
public:
    DropTableCommand(std::string tableName)
        : tableName_(std::move(tableName)) {}

    void execute(Database& db) override {
            db.dropTable(tableName_);
    }
};

// class InsertCommand : public Command {
// private:
//     std::string tableName_;
//     std::vector<InsertField> fields_;

// public:
//     InsertCommand(std::string table,
//                   std::vector<InsertField> fields)
//         : tableName_(std::move(table)),
//           fields_(std::move(fields)) {}

//     void execute(Database& db) override {
//         // db.insert(tableName_, fields_);
//     }
// };


#endif // COMMANDS_H