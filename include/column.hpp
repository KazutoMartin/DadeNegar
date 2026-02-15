#ifndef COLOUMN_H
#define COLOUMN_H

#include <string>

class Column {
protected:
    std::string name;
    bool required;

public:
    Column(std::string name, bool required)
        : name(std::move(name)), required(required) {}

    virtual ~Column() = default;

    const std::string& getName() const {
        return name;
    }

    bool isRequired() const {
        return required;
    }

    // برای تشخیص نوع در runtime
    virtual bool isInt() const = 0;
    virtual bool isString() const = 0;
};

class IntColumn : public Column {
public:
    IntColumn(const std::string& name, bool required)
        : Column(name, required) {}

    bool isInt() const override {
        return true;
    }

    bool isString() const override {
        return false;
    }
};
class StrColumn : public Column {
public:
    StrColumn(const std::string& name, bool required)
        : Column(name, required) {}

    bool isInt() const override {
        return false;
    }

    bool isString() const override {
        return true;
    }
};

#endif //COLOUMN_H