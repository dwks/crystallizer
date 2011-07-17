#ifndef CRYSTALLIZER_NETWORK__HIVE_THREAD_H
#define CRYSTALLIZER_NETWORK__HIVE_THREAD_H

#include "boost/shared_ptr.hpp"
#include "boost/asio/io_service.hpp"

#include "ServerSocket.h"
#include "WorkerList.h"

namespace Crystallizer {
namespace Network {

class HiveThread {
private:
    boost::shared_ptr<boost::asio::io_service> io_service;
    
    WorkerList workerList;
    boost::shared_ptr<ServerSocket> serverSocket;
    
    bool quit;
public:
    /** Note: this constructor will be called in the original thread's context,
        and then the copy constructor will make a copy of this class in the new
        thread. So this constructor should not do important initialization.
    */
    HiveThread();
    
    void operator ()();
};

}  // namespace Network
}  // namespace Crystallizer

#endif
