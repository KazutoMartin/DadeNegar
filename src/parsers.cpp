#include <memory>
#include <iostream>
#include <sstream>


#include "commands.hpp"
#include "enums.hpp"
#include "helpers.hpp"



using namespace std;


unique_ptr<Command> parseCreateTable(
    stringstream& ss, CommandType type) {

    string tableName;
    ss >> tableName;

    string rest;
    getline(ss, rest); // fields
    auto fields = parseFieldDefinitions(rest.substr(1));
    unique_ptr<Command> cmd;
    if (type == CommandType::CREATE_TABLE){
        cmd = make_unique<CreateTableCommand>(tableName,
                                                    fields);
    } else {
        cmd = make_unique<CreateEnhancedTableCommand>(tableName,
                                                            fields);
    }
        

    return cmd;
}

unique_ptr<Command> parseDropTable(stringstream& ss) {
    string tableName;
    ss >> tableName;
    unique_ptr<Command> cmd = make_unique<DropTableCommand>(tableName);
    return cmd;
}

// unique_ptr<Command> parseInsert(stringstream& ss) {
//     auto cmd = make_unique<InsertCommand>();
//     cmd->type = CommandType::INSERT;

//     string word;
//     ss >> word; // into
//     ss >> cmd->tableName;

//     string rest;
//     getline(ss, rest);
//     cmd->fields = parseInsertFields(rest.substr(1));

//     return cmd;
// }

// unique_ptr<Command> parseUpdate(stringstream& ss) {
//     auto cmd = make_unique<UpdateCommand>();
//     cmd->type = CommandType::UPDATE;

//     string word;
//     ss >> cmd->tableName;
//     ss >> word; // where

//     cmd->where = parseCondition(ss);

//     ss >> word; // set
//     ss >> cmd->updateField >> cmd->updateValue;

//     return cmd;
// }
