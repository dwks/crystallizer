#ifndef CRYSTALLIZER_WORKER__WORKER_MIND_H
#define CRYSTALLIZER_WORKER__WORKER_MIND_H

#include <string>

#include "boost/shared_array.hpp"

#include "network/DataReceiver.h"
#include "network/ClientSocket.h"

namespace Crystallizer {
namespace Worker {

class WorkerMind {
private:
    boost::shared_ptr<Network::ClientSocket> hive;
protected:
    class Receiver : public Network::DataReceiver {
    private:
        boost::shared_ptr<Network::ClientSocket> hive;
    public:
        Receiver(boost::shared_ptr<Network::ClientSocket> hive) : hive(hive) {}
        
        virtual bool receive(const std::string &data);
    };
    
    class MandelbrotReceiver : public Network::DataReceiver {
    private:
        boost::shared_ptr<Network::ClientSocket> hive;
    public:
        MandelbrotReceiver(boost::shared_ptr<Network::ClientSocket> hive)
            : hive(hive) {}
        
        virtual bool receive(const std::string &data);
    };
public:
    void run(const std::string &host, unsigned short port);
};

}  // namespace Worker
}  // namespace Crystallizer

#endif
