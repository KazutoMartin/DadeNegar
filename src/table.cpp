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