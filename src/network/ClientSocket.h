#ifndef CRYSTALLIZER_NETWORK__CLIENT_SOCKET_H
#define CRYSTALLIZER_NETWORK__CLIENT_SOCKET_H

#include <vector>

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/asio/ip/tcp.hpp"

#include "DataReceiver.h"

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
    
    typedef std::vector<boost::weak_ptr<DataReceiver> > ReceiverListType;
    ReceiverListType receiverList;
public:
    ClientSocket(boost::asio::io_service &io_service,
        const char *host, unsigned short port);
    ClientSocket(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
    
    void addReceiver(boost::shared_ptr<DataReceiver> receiver)
        { receiverList.push_back(receiver); }
    void addReceiverFront(boost::shared_ptr<DataReceiver> receiver)
        { receiverList.insert(receiverList.begin(), receiver); }
    
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
