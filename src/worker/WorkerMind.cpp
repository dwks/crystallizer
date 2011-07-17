#include <cstdlib>  // for std::exit

#include "WorkerMind.h"
#include "network/ClientSocket.h"

#include "config.h"
#include "log/Logger.h"

namespace Crystallizer {
namespace Worker {

void WorkerMind::run(const std::string &host, unsigned short port) {
    boost::asio::io_service io_service;
    boost::shared_ptr<Network::ClientSocket> hive;
    
    LOG2(GLOBAL, PROGRESS, "Worker trying hive " << host << ":" << port);
    
    try {
        hive = boost::shared_ptr<Network::ClientSocket>(
            new Network::ClientSocket(io_service, host.c_str(), port));
    }
    catch(std::exception &e) {
        LOG2(NETWORK, ERROR, "Exception: " << e.what());
        std::exit(1);
    }
    
    LOG2(GLOBAL, PROGRESS, "Entering tiny little worker mind");
}

}  // namespace Worker
}  // namespace Crystallizer
