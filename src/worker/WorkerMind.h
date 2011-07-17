#ifndef CRYSTALLIZER_WORKER__WORKER_MIND_H
#define CRYSTALLIZER_WORKER__WORKER_MIND_H

#include <string>

#include "network/DataReceiver.h"

namespace Crystallizer {
namespace Worker {

class WorkerMind {
protected:
    class Receiver : public Network::DataReceiver {
    public:
        virtual bool receive(const std::string &data);
    };
public:
    void run(const std::string &host, unsigned short port);
};

}  // namespace Worker
}  // namespace Crystallizer

#endif
