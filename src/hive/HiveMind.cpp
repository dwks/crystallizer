#include <iostream>
#include "HiveMind.h"
#include "network/HiveThread.h"

#include "boost/thread.hpp"

namespace Crystallizer {
namespace Hive {

void HiveMind::run() {
    Network::HiveThread hive;
    boost::shared_ptr<boost::thread> hiveThread(new boost::thread(hive));
    
    std::cout << "Hello, you have control of the Hive Mind. Please direct us.\n";
    std::string command;
    while(getCommand(command)) {
        if(command == "quit") {
            break;
        }
    }
    
    hiveThread->join();
}

bool HiveMind::getCommand(std::string &command) {
    std::cout << "> ";
    return std::getline(std::cin, command);
}

}  // namespace Hive
}  // namespace Crystallizer
