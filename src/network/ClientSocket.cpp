#include <sstream>
#include <iomanip>  // for std::left, std::setw

#include "boost/asio/placeholders.hpp"
#include "boost/asio/buffer.hpp"
#include "boost/asio/read.hpp"
#include "boost/asio/write.hpp"
#include "boost/bind.hpp"

#include "ClientSocket.h"

#include "misc/StreamAsString.h"
#include "log/Logger.h"

namespace Crystallizer {
namespace Network {

ClientSocket::ClientSocket(boost::asio::io_service &io_service,
    const char *host, unsigned short port) {
    
    using namespace boost::asio::ip;
    
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(host, Misc::StreamAsString() << port);
    tcp::resolver::iterator it = resolver.resolve(query);  // throws boost::system::system_error
    tcp::resolver::iterator end;
    
    socket = boost::shared_ptr<tcp::socket>(new tcp::socket(io_service));
    
    boost::system::error_code error = boost::asio::error::host_not_found;
    while(error && it != end) {
        if(socket->is_open()) socket->close();
        socket->connect(*it++, error);
    }
    
    if(error) {
        throw boost::system::system_error(error);
    }
    
    registerReadHeaderHandler();
}

ClientSocket::ClientSocket(
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket) : socket(socket) {
    
    registerReadHeaderHandler();
}

void ClientSocket::send(const std::string &data) {
    LOG(NETWORK, "Sending packet [" << escape(data) << "]");
    
    outputData = data;
    
    // format header
    std::ostringstream headerStream;
    headerStream << std::left << std::setw(HEADER_SIZE) << outputData.size();
    outputHeader = headerStream.str();
    
    if(static_cast<int>(outputHeader.size()) != HEADER_SIZE) {
        LOG2(NETWORK, ERROR, "Can't create packet header; packet size "
            << outputData.size() << " may be too large");
        return;
    }
    
    // use gather-write to send header+data at the same time
    std::vector<boost::asio::const_buffer> bufferList;
    bufferList.push_back(boost::asio::buffer(outputHeader));
    bufferList.push_back(boost::asio::buffer(outputData));
    boost::asio::async_write(*socket, bufferList,
        boost::bind(&ClientSocket::doneAsyncWrite, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void ClientSocket::doneAsyncWrite(const boost::system::error_code &error,
    std::size_t bytes) {
    
    LOG(NETWORK, "Done asynchronous write of " << bytes << " bytes");
}

void ClientSocket::registerReadHeaderHandler() {
    // read exactly as many bytes as are in the inputHeader (i.e. HEADER_SIZE)
    boost::asio::async_read(*socket, boost::asio::buffer(inputHeader),
        boost::bind(&ClientSocket::readHeaderHandler,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void ClientSocket::readHeaderHandler(const boost::system::error_code &error,
    std::size_t bytes) {
    
    if(error == boost::asio::error::eof) {
        // connection closed cleanly by peer
        LOG2(NETWORK, CONNECT, "Connection closed by peer");
        return;
    }
    else if(error) {
        throw boost::system::system_error(error);
    }
    
    std::istringstream stream(std::string(inputHeader, sizeof(inputHeader)));
    int size;
    stream >> size;
    
    buffer.resize(size);
    LOG(NETWORK, "Incoming packet of size " << size);
    
    registerReadDataHandler();
}

void ClientSocket::registerReadDataHandler() {
    // it is assumed that buffer has already been resized to the size of the
    // incoming data
    boost::asio::async_read(*socket, boost::asio::buffer(buffer),
        boost::bind(&ClientSocket::readDataHandler,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void ClientSocket::readDataHandler(const boost::system::error_code &error,
    std::size_t bytes) {
    
    if(error == boost::asio::error::eof) {
        // connection closed cleanly by peer
        LOG2(NETWORK, CONNECT, "Connection closed by peer");
        return;
    }
    else if(error) {
        throw boost::system::system_error(error);
    }
    
    std::string data(&buffer[0], buffer.size());
    LOG(NETWORK, "Received packet [" << escape(data) << "]");
    
    for(ReceiverListType::size_type x = 0; x < receiverList.size(); x ++) {
        //LOG(NETWORK, "Observer " << x << " " << &receiverList[x]);
        if(receiverList[x]->receive(data)) {
            // keep this observer
            break;
        }
        else {
            // throw away this observer
            receiverList.erase(receiverList.begin() + x);
            x --;
            break;
        }
    }
    
    registerReadHeaderHandler();
}

std::string ClientSocket::escape(const std::string &data) {
    Misc::StreamAsString stream;
    
    for(std::string::size_type i = 0; i < data.size(); i ++) {
        switch(data[i]) {
        case '\0':
            stream << "\\0";
            break;
        case '\n':
            stream << "\\n";
            break;
        default:
            stream << data[i];
            break;
        }
    }
    
    return stream;
}

}  // namespace Network
}  // namespace Crystallizer
