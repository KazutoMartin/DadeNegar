#include <iostream>
#include <memory>
#include <sstream>



#include "commands.hpp"
#include "exceptions.hpp"
#include "parsers.hpp"
#include "database.hpp"


#define CMD_CREATE_TABLE            "create_table"
#define CMD_CREATE_ENHANCED_TABLE   "create_enhanced_table"
#define CMD_DROP_TABLE              "drop_table"
#define CMD_INSERT                  "insert"
#define CMD_UPDATE                  "update"
#define CMD_SELECT                  "select"




std::unique_ptr<Command> processCommand(const std::string& line) {
    std::stringstream ss(line);
    std::string cmd;
    ss >> cmd;

    if (cmd == CMD_CREATE_TABLE)
        return parseCreateTable(ss, CommandType::CREATE_TABLE);

    if (cmd == CMD_CREATE_ENHANCED_TABLE)
        return parseCreateTable(ss, CommandType::CREATE_ENHANCED_TABLE);

    if (cmd == CMD_DROP_TABLE)
        return parseDropTable(ss);

    if (cmd == CMD_INSERT)
        return parseInsert(ss);

    // if (cmd == CMD_UPDATE)
    //     return parseUpdate(ss);

    // if (cmd == CMD_SELECT)
    //     return parseSelect(ss);
}

int main()
{
    Database db = Database();
    std::string ln;
    while (std::getline(std::cin, ln))
    {
        try
        {
            std::unique_ptr<Command> command = processCommand(ln);

            if (!command) {
                std::cout << "Error: Invalid command\n";
                continue;
            }
            command->execute(db);
        }
        catch (const DatabaseException& ex)
        {
            std::cout << ex.what() << "\n";
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << "\n";
        }
    }
    return 0;
}