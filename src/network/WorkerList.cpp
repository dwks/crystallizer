#include "WorkerList.h"

namespace Crystallizer {
namespace Network {

void WorkerList::addWorker(boost::shared_ptr<ClientSocket> socket) {
    list.push_back(socket);
}

}  // namespace Network
}  // namespace Crystallizer
