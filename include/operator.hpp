#ifndef OPERATOR_H
#define OPERATOR_H

#include <variant>
#include <string>

using namespace std;

using Value = variant<int, string>;

using CompareFunction = bool(*)(const Value&, const Value&);


bool equalOp(const Value& a, const Value& b);

bool notEqualOp(const Value& a, const Value& b);

bool lessThanOp(const Value& a, const Value& b);


class Operator {
    CompareFunction cmp_;

public:
    Operator(CompareFunction cmp)
        : cmp_(cmp) {}

    bool apply(const Value& lhs, const Value& rhs) const {
        return cmp_(lhs, rhs);
    }
};

#endif //OPERATOR_H