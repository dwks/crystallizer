#ifndef CRYSTALLIZER_HIVE__HIVE_MIND_H
#define CRYSTALLIZER_HIVE__HIVE_MIND_H

#include <string>

namespace Crystallizer {
namespace Hive {

class HiveMind {
public:
    void run();
private:
    bool getCommand(std::string &command);
};

}  // namespace Hive
}  // namespace Crystallizer

#endif
