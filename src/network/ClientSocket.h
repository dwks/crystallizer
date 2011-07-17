#ifndef CRYSTALLIZER_NETWORK__CLIENT_SOCKET_H
#define CRYSTALLIZER_NETWORK__CLIENT_SOCKET_H

#include "boost/shared_ptr.hpp"
#include "boost/asio/ip/tcp.hpp"

namespace Crystallizer {
namespace Network {

class ClientSocket {
private:
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
    
    static const int HEADER_SIZE = 8;
    std::string outputHeader;
    std::string outputData;
    char inputHeader[HEADER_SIZE];
    
    std::vector<char> buffer;
public:
    ClientSocket(boost::asio::io_service &io_service,
        const char *host, unsigned short port);
    ClientSocket(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
    
    void send(const std::string &data);
protected:
    void doneAsyncWrite(const boost::system::error_code &error,
        std::size_t bytes);
    
    void registerReadHeaderHandler();
    void readHeaderHandler(const boost::system::error_code &error,
        std::size_t bytes);
    void registerReadDataHandler();
    void readDataHandler(const boost::system::error_code &error,
        std::size_t bytes);
private:
    static std::string escape(const std::string &data);
};

}  // namespace Network
}  // namespace Crystallizer

#endif
