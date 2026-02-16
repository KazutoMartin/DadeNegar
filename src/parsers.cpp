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


unique_ptr<Command> parseInsert(stringstream& ss) {
    
    string word;
    ss >> word; // into
    string tableName;
    ss >> tableName;
    
    string rest;
    getline(ss, rest);
    unordered_map<string, string> fields = parseInsertFields(rest.substr(1));
    unique_ptr<InsertCommand> cmd = make_unique<InsertCommand>(tableName, fields);
    
    return cmd;
}

unique_ptr<Command> parseUpdate(stringstream& ss) {
    string tableName;
    string updateField;
    string updateValue;
    string opSymbol;
    string whereField;
    string fieldValue;

    
    string word;
    ss >> tableName;
    ss >> word; // where


    ss >> whereField >> opSymbol >> fieldValue;
    CompareFunction compare = identifyOperatorSymbol(opSymbol);
    unique_ptr<Operator> op = make_unique<Operator>(compare);
    
    ss >> word; // set
    ss >> updateField >> updateValue;
    
    unique_ptr<UpdateCommand> cmd = make_unique<UpdateCommand>(tableName,
                                                                whereField,
                                                                fieldValue,
                                                                move(op),
                                                                updateField,
                                                                updateValue
                                                            );                                           
    return cmd;
}
