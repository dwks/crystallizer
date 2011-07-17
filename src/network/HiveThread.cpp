#include "HiveThread.h"
#include <unistd.h>  // sorry

#include "boost/thread/thread.hpp"

#include "log/Logger.h"
#include "config.h"

namespace Crystallizer {
namespace Network {

HiveThread::HiveThread() {
    quit = false;
}

void HiveThread::operator ()() {
    LOG2(GLOBAL, PROGRESS, "Starting HiveThread, id "
        << boost::this_thread::get_id() << " address " << this);
    
    try {
        io_service = boost::shared_ptr<boost::asio::io_service>(
            new boost::asio::io_service());
        serverSocket = boost::shared_ptr<ServerSocket>(
            new ServerSocket(*io_service, DEFAULT_PORT));
        serverSocket->setWorkerList(&workerList);
    }
    catch(std::exception &e) {
        LOG2(NETWORK, ERROR, "Exception: " << e.what());
    }
    
    while(!quit) {
        LOG(NETWORK, "Network loop...");
        
        try {
            io_service->run();
            io_service->reset();
        }
        catch(std::exception &e) {
            LOG2(NETWORK, ERROR, "Exception: " << e.what());
        }
        
        if(!quit) {
            sleep(1);
        }
    }
}

}  // namespace Network
}  // namespace Crystallizer
