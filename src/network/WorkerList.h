#ifndef CRYSTALLIZER_NETWORK__WORKER_LIST_H
#define CRYSTALLIZER_NETWORK__WORKER_LIST_H

#include <vector>
#include "boost/shared_ptr.hpp"

#include "ClientSocket.h"

namespace Crystallizer {
namespace Network {

class WorkerList {
private:
    typedef std::vector<boost::shared_ptr<ClientSocket> > ListType;
    ListType list;
public:
    void addWorker(boost::shared_ptr<ClientSocket> socket);
};

}  // namespace Network
}  // namespace Crystallizer

#endif
