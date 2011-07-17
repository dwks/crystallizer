#ifndef CRYSTALLIZER_NETWORK__SERVER_SOCKET_H
#define CRYSTALLIZER_NETWORK__SERVER_SOCKET_H

#include "boost/shared_ptr.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/io_service.hpp"

namespace Crystallizer {
namespace Network {

class ServerSocket {
private:
    boost::shared_ptr<boost::asio::ip::tcp::socket> newSocket;
    boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;
public:
    ServerSocket(boost::asio::io_service &io_service, unsigned short port);
protected:
    void registerAcceptHandler(boost::asio::io_service &io_service);
    void acceptHandler(const boost::system::error_code &error);
};

}  // namespace Network
}  // namespace Crystallizer

#endif
