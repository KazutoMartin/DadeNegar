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

    unordered_map<string, shared_ptr<Column>> columns;

    for (const auto& field : fields) {
        columns[field.name] = makeColumn(field);
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

    unordered_map<string, shared_ptr<Column>> columns;
    shared_ptr<Column> primaryKey;

    for (const auto& field : fields) {
        auto column = makeColumn(field);
        columns[field.name] = column;

        if (field.required) {
            primaryKey = column;
        }
    }

    shared_ptr<BaseTable> table = make_shared<AdvancedTable>(tableName, columns, primaryKey);

    tables_[tableName] = table;

    cout << "Success: Table " << tableName << " created successfully" << endl;

}



void Database::dropTable(string tableName){
    if (!getTable(tableName)){
        throw TableDoesNotExistException(tableName);
    }

    tables_.erase(tableName);

    cout << "Success: Table " << tableName << " deleted successfully" << endl;

}

void Database::insert(string tableName, unordered_map<string, string> fields){
    shared_ptr<BaseTable> table = getTable(tableName);
    if (!table){
        throw TableDoesNotExistException(tableName);
    }

    table->insertRow(fields);


    cout << "Success: Record inserted into table successfully" << endl;

}



void Database::update(const std::string& tableName,
                      const std::string& whereField,
                      const std::string& fieldValue,
                      const Operator& op,
                      const std::string& updateField,
                      const std::string& updateValue)
{
    shared_ptr<BaseTable> table = getTable(tableName);
    if (!table){
        throw TableDoesNotExistException(tableName);
    }

    table->update(whereField, fieldValue, op, updateField, updateValue);

    cout << "Success: Records updated in table" << endl;
}

void Database::select(const std::string& tableName,
                      const std::string& whereField,
                      const std::string& fieldValue,
                      const Operator& op,
                      vector<string> requestedFields
                      )
{
    shared_ptr<BaseTable> table = getTable(tableName);
    if (!table){
        throw TableDoesNotExistException(tableName);
    }

    vector<unordered_map<string, Value>> selectedRows = table->select(whereField, fieldValue, op, requestedFields);

    // assuming requested fields length is always one.
    for (const auto& row : selectedRows){
        printVariantValue(row.at(whereField));
        cout << " : ";
        printVariantValue(row.at(requestedFields[0]));
        cout << endl;
    }

}

