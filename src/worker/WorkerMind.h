#ifndef CRYSTALLIZER_WORKER__WORKER_MIND_H
#define CRYSTALLIZER_WORKER__WORKER_MIND_H

#include <string>

namespace Crystallizer {
namespace Worker {

class WorkerMind {
public:
    void run(const std::string &host, unsigned short port);
};

}  // namespace Worker
}  // namespace Crystallizer

#endif
