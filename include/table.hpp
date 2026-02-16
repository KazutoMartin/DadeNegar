#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <string>
#include <memory>
#include <variant> 


#include "exceptions.hpp" 
#include "column.hpp"

using namespace std;



#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "column.hpp"

using namespace std;
using Value = variant<int, std::string>;

class BaseTable {
protected:
    string tableName_;
    unordered_map<string, shared_ptr<Column>> columns_;
    vector<unordered_map<string, Value>> rows_;

public:
    BaseTable(string tableName,
          unordered_map<string, shared_ptr<Column>> columns);

    virtual ~BaseTable() = default;

    const string& getName() const;
    const unordered_map<string, shared_ptr<Column>>& getColumns() const;

    virtual void insertRow(const unordered_map<string, string>& row) = 0;


    virtual bool isAdvanced() const = 0;
};


class SimpleTable : public BaseTable {
public:
    SimpleTable(string tableName,
            unordered_map<string, shared_ptr<Column>> columns);

    void insertRow(const unordered_map<string, string>& row);

    bool isAdvanced() const override;
};


class AdvancedTable : public BaseTable {
private:
    shared_ptr<Column> primaryKeyColumn;
public:
    AdvancedTable(string tableName,
              unordered_map<string, shared_ptr<Column>> columns,
              shared_ptr<Column> primaryKeyColumn);

    void insertRow(const unordered_map<string, string>& row) override;

    bool isAdvanced() const override;
};
#endif