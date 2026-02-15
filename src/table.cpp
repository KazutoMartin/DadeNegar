#include "table.hpp"

using namespace std;

BaseTable::BaseTable(
    string tableName,
    vector<shared_ptr<Column>> columns
)
    : tableName_(move(tableName)),
      columns_(columns)
{
}

const string& BaseTable::getName() const {
    return tableName_;
}

const vector<shared_ptr<Column>>& BaseTable::getColumns() const {
    return columns_;
}

SimpleTable::SimpleTable(
    string tableName,
    vector<shared_ptr<Column>> columns
)
    : BaseTable(move(tableName), columns)
{
}

AdvancedTable::AdvancedTable(string tableName,
                vector<shared_ptr<Column>> columns,
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