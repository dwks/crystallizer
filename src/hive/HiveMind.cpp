#include <iostream>
#include "HiveMind.h"

#include "boost/asio/io_service.hpp"

namespace Crystallizer {
namespace Hive {

void HiveMind::run() {
    std::cout << "Hello, you have control of the Hive Mind. Please direct us.\n";
    std::string command;
    while(getCommand(command)) {
        if(command == "quit") {
            break;
        }
    }
}

bool HiveMind::getCommand(std::string &command) {
    std::cout << "> ";
    return std::getline(std::cin, command);
}

}  // namespace Hive
}  // namespace Crystallizer
