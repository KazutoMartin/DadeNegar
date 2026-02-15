#include <vector>
#include <string>
#include <memory>

#include "column.hpp"

using namespace std;



#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "column.hpp"

using namespace std;

class BaseTable {
protected:
    string tableName_;
    unordered_map<string, shared_ptr<Column>> columns_;

public:
    BaseTable(string tableName,
          unordered_map<string, shared_ptr<Column>> columns);

    virtual ~BaseTable() = default;

    const string& getName() const;
    const unordered_map<string, shared_ptr<Column>>& getColumns() const;


    virtual bool isAdvanced() const = 0;
};


class SimpleTable : public BaseTable {
public:
    SimpleTable(string tableName,
            unordered_map<string, shared_ptr<Column>> columns);

    bool isAdvanced() const override;
};

class AdvancedTable : public BaseTable {
private:
    shared_ptr<Column> primaryKeyColumn;
public:
    AdvancedTable(string tableName,
              unordered_map<string, shared_ptr<Column>> columns,
              shared_ptr<Column> primaryKeyColumn);

    bool isAdvanced() const override;
};
#endif