#include "table.hpp"

#include <iostream>


using namespace std;

BaseTable::BaseTable(
    string tableName,
    unordered_map<string, shared_ptr<Column>> columns
)
    : tableName_(move(tableName)),
      columns_(columns)
{
}

const string& BaseTable::getName() const {
    return tableName_;
}

const unordered_map<string, shared_ptr<Column>>& BaseTable::getColumns() const {
    return columns_;
}

SimpleTable::SimpleTable(
    string tableName,
    unordered_map<string, shared_ptr<Column>> columns
)
    : BaseTable(move(tableName), columns)
{
}

AdvancedTable::AdvancedTable(
    string tableName,
    unordered_map<string, shared_ptr<Column>> columns,
    shared_ptr<Column> primaryKeyColumn
)
            : BaseTable(move(tableName), columns), primaryKeyColumn(primaryKeyColumn) 
{
}

bool SimpleTable::isAdvanced() const {
    return false;
}

bool AdvancedTable::isAdvanced() const {
    return true;
}

void SimpleTable::insertRow(const unordered_map<string, string>& row){
    unordered_map<string, Value> storedRow;

    for (const auto& [columnName, columnPtr] : columns_) {

        auto it = row.find(columnName);
        if (it == row.end()) {
            if (columnPtr->isRequired()) {
                throw MissingRequiredFieldException();
            }
            continue;
        }

        storedRow[columnName] = columnPtr->convertValue(it->second);
    }

    rows_.push_back(storedRow);
}

void AdvancedTable::insertRow(const unordered_map<string, string>& row){
    unordered_map<string, Value> storedRow;

    for (const auto& [columnName, columnPtr] : columns_) {

        auto it = row.find(columnName);
        if (it == row.end()) {
            if (columnPtr->isRequired()) {
                throw MissingRequiredFieldException();
            }
            continue;
        }

        storedRow[columnName] = columnPtr->convertValue(it->second);
    }

    const string& pkName = primaryKeyColumn->getName();


    auto pkIt = storedRow.find(pkName);


    const Value& newPkValue = pkIt->second;


    for (const auto& existingRow : rows_) {
        auto it = existingRow.find(pkName);
        if (it != existingRow.end() && it->second == newPkValue) {
            throw DuplicateRequiredValueException();
        }
    }

    rows_.push_back(storedRow);
}


void BaseTable::update(const string &whereField,
                        const string &fieldValue,
                        const Operator &op, 
                        const string &updateField, 
                        const string &updateValue)
{
    shared_ptr<Column> updateCol = getColumn(updateField);
    shared_ptr<Column> whereCol = getColumn(whereField);


    Value newVal = updateCol->convertValue(updateValue);
    Value value = whereCol->convertValue(fieldValue);

    
    
    
    for (auto& row : rows_) {
        if (op.apply(row[whereField], value)) {
            row[updateField] = newVal;
        }
    }
    
}


vector<unordered_map<string, Value>> SimpleTable::select(const string &whereField, const string &fieldValue, const Operator &op, vector<string> requestedFields){
    shared_ptr<Column> whereCol = getColumn(whereField);

    Value value = whereCol->convertValue(fieldValue);

    vector<unordered_map<string, Value>> selectedRows;

    bool foundFlag = false;
     
    for (auto& row : rows_) {
        if (op.apply(row.at(whereField), value)) {

            unordered_map<string, Value> filteredRow;

            for (const auto& field : requestedFields) {
                filteredRow[field] = row.at(field);
            }
            filteredRow[whereField] = row.at(whereField);

            selectedRows.push_back(std::move(filteredRow));
            foundFlag = true;
        }
    }

    if (!foundFlag){
        throw NoMatchingRecordException();
    }

    return selectedRows;
    
}

vector<unordered_map<string, Value>> AdvancedTable::sortSelectedRows(vector<unordered_map<string, Value>> selectedRows) {
    
    string primaryKeyName = primaryKeyColumn->getName();

    sort(
        selectedRows.begin(),
        selectedRows.end(),
        [&](unordered_map<string, Value> a,
            unordered_map<string, Value> b) {

            return a.at(primaryKeyName) < b.at(primaryKeyName);
        }
    );

    return selectedRows;
}
vector<unordered_map<string, Value>> AdvancedTable::select(const string &whereField, const string &fieldValue, const Operator &op, vector<string> requestedFields){
    shared_ptr<Column> whereCol = getColumn(whereField);

    Value value = whereCol->convertValue(fieldValue);

    vector<unordered_map<string, Value>> selectedRows;

    bool foundFlag = false;
     
    for (auto& row : rows_) {
        if (op.apply(row.at(whereField), value)) {

            unordered_map<string, Value> filteredRow;

            for (const auto& field : requestedFields) {
                auto it = row.find(field);
                filteredRow[field] = it->second;
            }

            selectedRows.push_back(std::move(filteredRow));
            foundFlag = true;
        }
    }

    if (!foundFlag){
        throw NoMatchingRecordException();
    }

    sortSelectedRows(selectedRows);

    return selectedRows;
    
}
