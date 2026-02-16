#ifndef COMMANDS_H
#define COMMANDS_H

#include "enums.hpp"
#include "utils.hpp"
#include "database.hpp"
#include "operator.hpp"


#include <iostream>


using namespace std;

class Database; 


class Command {
public:
    virtual ~Command() = default;

    virtual void execute(Database& db) = 0;
};

class CreateTableCommand : public Command {
private:
    string tableName_;
    vector<FieldDefinition> fields_;

public:
    CreateTableCommand(string tableName,
                       vector<FieldDefinition> fields
                    )
        : tableName_(move(tableName)),
          fields_(move(fields)) {}

    void execute(Database& db) override {
            db.createTable(tableName_, fields_);
    }
};

class CreateEnhancedTableCommand : public Command {
private:
    string tableName_;
    vector<FieldDefinition> fields_;

public:
    CreateEnhancedTableCommand(string tableName,
                       vector<FieldDefinition> fields
                    )
        : tableName_(move(tableName)),
          fields_(move(fields)) {}

    void execute(Database& db) override {
            db.createEnhancedTable(tableName_, fields_);
    }
};


class DropTableCommand : public Command {
private:
    string tableName_;
public:
    DropTableCommand(string tableName)
        : tableName_(move(tableName)) {}

    void execute(Database& db) override {
            db.dropTable(tableName_);
    }
};

class InsertCommand : public Command {
private:
    string tableName_;
    unordered_map<string, string> fields_;

public:
    InsertCommand(string table,
                  unordered_map<string, string> fields)
        : tableName_(move(table)),
          fields_(move(fields)) {}

    void execute(Database& db) override {
        db.insert(tableName_, fields_);
    }
};

class UpdateCommand : public Command {
private:
    string tableName_;

    string whereField_;
    string fieldValue_;

    unique_ptr<Operator> op_;


    string updateField_;
    string updateValue_;   

public:
    UpdateCommand(string tableName,
                  string whereField,
                  string fieldValue,
                  unique_ptr<Operator> op,
                  string updateField,
                  string updateValue)
        : tableName_(move(tableName)),
          whereField_(move(whereField)),
          fieldValue_(move(fieldValue)),
          op_(move(op)),
          updateField_(move(updateField)),
          updateValue_(move(updateValue)) {}

    void execute(Database& db) override {
        db.update(
            tableName_,
            whereField_,
            fieldValue_,
            *op_,
            updateField_,
            updateValue_
        );
    }
};

class SelectCommand : public Command {
private:
    string tableName_;

    string whereField_;
    string fieldValue_;
    
    unique_ptr<Operator> op_;


    vector<string> requestedFields_;

public:
    SelectCommand(string tableName,
                  string whereField,
                  string fieldValue,
                  unique_ptr<Operator> op,
                  vector<string> requestedFields
                  )
        : tableName_(move(tableName)),
          whereField_(move(whereField)),
          fieldValue_(move(fieldValue)),
          op_(move(op)),
          requestedFields_(move(requestedFields))
         {}

    void execute(Database& db) override {
        db.select(
            tableName_,
            whereField_,
            fieldValue_,
            *op_,
            requestedFields_
        );
    }
};



#endif // COMMANDS_H