#include "ServerSocket.h"
#include "WorkerList.h"

#include "boost/bind.hpp"
#include "boost/asio/placeholders.hpp"

#include "log/Logger.h"

namespace Crystallizer {
namespace Network {

ServerSocket::ServerSocket(boost::asio::io_service &io_service,
    unsigned short port) {
    
    using namespace boost::asio::ip;
    
    acceptor = boost::shared_ptr<tcp::acceptor>(new tcp::acceptor(
        io_service,
        tcp::endpoint(tcp::v4(), port)));
    
    registerAcceptHandler(io_service);
}

void ServerSocket::registerAcceptHandler(boost::asio::io_service &io_service) {
    using namespace boost::asio::ip;
    
    newSocket = boost::shared_ptr<tcp::socket>(new tcp::socket(io_service));
    
    acceptor->async_accept(*newSocket,
        boost::bind(&ServerSocket::acceptHandler,
            this,
            boost::asio::placeholders::error));
}

void ServerSocket::acceptHandler(const boost::system::error_code &error) {
    if(error) {
        throw boost::system::system_error(error);
    }
    
    LOG2(NETWORK, CONNECT, "New socket connection from "
        << newSocket->remote_endpoint().address().to_string()
        << ":"
        << newSocket->remote_endpoint().port());
    
    list->addWorker(
        boost::shared_ptr<ClientSocket>(new ClientSocket(newSocket)));
    
    // discard reference to the socket
    newSocket.reset();
    
    registerAcceptHandler(acceptor->io_service());
}

}  // namespace Network
}  // namespace Crystallizer
