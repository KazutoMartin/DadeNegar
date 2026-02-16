#ifndef COLOUMN_H
#define COLOUMN_H

#include <string>

using namespace std;

using Value = variant<int, string>;


class Column {
protected:
    string name;
    bool required;

public:
    Column(string name, bool required)
        : name(move(name)), required(required) {}

    virtual ~Column() = default;

    const string& getName() const {
        return name;
    }

    bool isRequired() const {
        return required;
    }


    virtual Value convertValue(const string& input) const = 0;
};

class IntColumn : public Column {
public:
    IntColumn(const string& name, bool required)
        : Column(name, required) {}

    Value convertValue(const string& input) const override {
        return stoi(input);
    }
};
class StrColumn : public Column {
public:
    StrColumn(const string& name, bool required)
        : Column(name, required) {}

    Value convertValue(const string& input) const override {
        return input;
    }
};

#endif //COLOUMN_H