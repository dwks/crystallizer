#ifndef SERIALIZER_LOG__TYPE_REGISTRY_H
#define SERIALIZER_LOG__TYPE_REGISTRY_H

#include <map>
#include <string>

#include "Subsystem.h"

namespace Crystallizer {
namespace Log {

class TypeRegistry {
private:
    static TypeRegistry instance;
public:
    static TypeRegistry &getInstance() { return instance; }
private:
    typedef std::map<std::string, int> type_list_t;
    type_list_t type_list[Subsystem::SUBSYSTEMS];
protected:
    TypeRegistry();
    void registerType(Subsystem subsystem, const std::string &type, int level);
    void addNextType(Subsystem subsystem, const std::string &type);
public:
    bool isValidType(Subsystem subsystem, const std::string &type);
    int getLevelOfType(Subsystem subsystem, const std::string &type);
};

}  // namespace Log
}  // namespace Crystallizer

#endif
