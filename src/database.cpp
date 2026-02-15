#include "database.hpp"
#include "exceptions.hpp"
#include "helpers.hpp"
#include "column.hpp"


#include <memory>
#include <iostream>


using namespace std;



shared_ptr<BaseTable> Database::getTable(const string& tableName) const{
    auto it = tables_.find(tableName);
    if (it != tables_.end()) {
        return it->second;
    }
    return nullptr;
}


shared_ptr<Column>
makeColumn(const FieldDefinition& field)
{
    if (field.type == ColumnType::INT)
        return make_shared<IntColumn>(field.name, field.required);

    return make_shared<StrColumn>(field.name, field.required);
}

void Database::createTable(string tableName, vector<FieldDefinition> fields){
    if (getTable(tableName)){
        throw TableAlreadyExistsException();
    }

    if (checkFieldNameDuplication(fields)){
        throw DuplicateFieldNameException();
    }

    vector<shared_ptr<Column>> columns;
    columns.reserve(fields.size());

    for (const auto& field : fields) {
        columns.push_back(makeColumn(field));
    }

    shared_ptr<BaseTable> table =  make_shared<SimpleTable>(tableName, columns);


    tables_[tableName] = table;

    cout << "Success: Table " << tableName << " created successfully" << endl;
}


void Database::createEnhancedTable(string tableName, vector<FieldDefinition> fields){
    if (getTable(tableName)){
        throw TableAlreadyExistsException();
    }

    if (checkFieldNameDuplication(fields)){
        throw DuplicateFieldNameException();
    }

    vector<shared_ptr<Column>> columns;
    columns.reserve(fields.size());
    shared_ptr<Column> primaryKey;

    for (const auto& field : fields) {
        shared_ptr<Column> newColumn = makeColumn(field);
        if (field.required){
            primaryKey = makeColumn(field);
            newColumn = primaryKey;
        }
        columns.push_back(newColumn);
    }

    shared_ptr<BaseTable> table = make_shared<AdvancedTable>(tableName, columns, primaryKey);

    tables_[tableName] = table;

    cout << "Success: Table " << tableName << " created successfully" << endl;

}



void Database::dropTable(string tableName){
    if (!getTable(tableName)){
        throw TableDoesNotExistException();
    }

    tables_.erase(tableName);

    cout << "Success: Table " << tableName << " deleted successfully" << endl;

}

