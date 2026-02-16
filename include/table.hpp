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
#include <stdexcept>


#include "column.hpp"
#include "operator.hpp"


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

    shared_ptr<Column> getColumn(const string& columnName) const {
        auto it = columns_.find(columnName);
        if (it == columns_.end()) {
            throw std::runtime_error("Column not found: " + columnName);
        }
        return it->second;
    }

    virtual void insertRow(const unordered_map<string, string>& row) = 0;
    virtual void update(const string &whereField, const string &fieldValue, const Operator &op, const string &updateField, const string &updateValue) = 0;


    virtual bool isAdvanced() const = 0;
};


class SimpleTable : public BaseTable {
public:
    SimpleTable(string tableName,
            unordered_map<string, shared_ptr<Column>> columns);

    void insertRow(const unordered_map<string, string>& row) override;
    void update(const string &whereField, const string &fieldValue, const Operator &op, const string &updateField, const string &updateValue) override;


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

    void update(const string &whereField, const string &fieldValue, const Operator &op, const string &updateField, const string &updateValue) override;


    bool isAdvanced() const override;
};
#endif