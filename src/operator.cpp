#include "operator.hpp"

bool equalOp(const Value& a, const Value& b) {
    return a == b;
}

bool notEqualOp(const Value& a, const Value& b) {
    return !equalOp(a, b);
}

bool lessThanOp(const Value& a, const Value& b) {
    return get<int>(a) < get<int>(b);
}
