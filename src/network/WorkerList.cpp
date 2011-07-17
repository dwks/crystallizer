#include "WorkerList.h"

namespace Crystallizer {
namespace Network {

void WorkerList::addWorker(boost::shared_ptr<ClientSocket> socket) {
    list.push_back(socket);
    socket->send("Mandelbrot");
    socket->send("-2.5 -1.25 1.0 1.25 0.05 0.05");
}

}  // namespace Network
}  // namespace Crystallizer
