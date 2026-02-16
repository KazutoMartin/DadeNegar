#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class DatabaseException : public std::exception {
protected:
    std::string message;

public:
    DatabaseException(std::string m) : message(std::move(m)) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class TableAlreadyExistsException : public DatabaseException {
public:
    TableAlreadyExistsException()
        : DatabaseException("Error: with table A this name already exists") {}
};

class DuplicateFieldNameException : public DatabaseException {
public:
    DuplicateFieldNameException()
        : DatabaseException("Error: Duplicate field name in table definition") {}
};

class TableDoesNotExistException : public DatabaseException {
public:
    TableDoesNotExistException()
        : DatabaseException("Error: Table does not exist") {}
};

class MissingRequiredFieldException : public DatabaseException {
public:
    MissingRequiredFieldException()
        : DatabaseException("Error: Missing value for required field") {}
};

class DuplicateRequiredValueException : public DatabaseException {
public:
    DuplicateRequiredValueException()
        : DatabaseException("Error: Duplicate value for required field") {}
};

class NoMatchingRecordException : public DatabaseException {
public:
    NoMatchingRecordException()
        : DatabaseException("Error: No found records matching") {}
};

#endif // EXCEPTIONS_H