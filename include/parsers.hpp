#ifndef PARSER_H
#define PARSER_H


#include <memory>
#include "commands.hpp"



std::unique_ptr<Command> parseCreateTable(
    std::stringstream& ss, CommandType type);

std::unique_ptr<Command> parseDropTable(std::stringstream& ss);

std::unique_ptr<Command> parseInsert(std::stringstream& ss);

std::unique_ptr<Command> parseUpdate(std::stringstream& ss);

std::unique_ptr<Command> parseSelect(std::stringstream& ss);

#endif // PARSER_H