#include <cstdlib>  // for std::exit
#include <unistd.h>  // sorry

#include "boost/bind.hpp"

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
    
    boost::shared_ptr<Network::DataReceiver> receiver(new Receiver());
    hive->addReceiver(receiver);
    
    LOG2(GLOBAL, PROGRESS, "Entering tiny little worker mind");
    
    for(;;) {
        LOG(NETWORK, "Worker loop...");
        
        try {
            io_service.run();
            io_service.reset();
        }
        catch(std::exception &e) {
            LOG2(NETWORK, ERROR, "Exception: " << e.what());
        }
    }
}

bool WorkerMind::Receiver::receive(const std::string &data) {
    if(data == "Mandelbrot") {
        LOG(NETWORK, "Worker is beginning a " << data);
    }
    else {
        LOG2(NETWORK, ERROR, "Unexpected packet received!");
    }
    
    return false;
}

}  // namespace Worker
}  // namespace Crystallizer
