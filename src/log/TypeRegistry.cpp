#include "TypeRegistry.h"

namespace Crystallizer {
namespace Log {

TypeRegistry TypeRegistry::instance;

TypeRegistry::TypeRegistry() {
    addNextType(Subsystem::GLOBAL, "ERROR");
    addNextType(Subsystem::GLOBAL, "WARNING");
    addNextType(Subsystem::GLOBAL, "PROGRESS");
    
    addNextType(Subsystem::NETWORK, "ERROR");
    
    addNextType(Subsystem::FRACTAL, "ERROR");
}

void TypeRegistry::registerType(Subsystem subsystem,
    const std::string &type, int level) {
    
    type_list[subsystem.getSubsystem()][type] = level;
}

void TypeRegistry::addNextType(Subsystem subsystem, const std::string &type) {
    type_list_t &list = type_list[subsystem.getSubsystem()];
    
    int level = static_cast<int>(list.size());
    
    registerType(subsystem, type, level);
}

bool TypeRegistry::isValidType(Subsystem subsystem, const std::string &type) {
    type_list_t::iterator found
        = type_list[subsystem.getSubsystem()].find(type);
    
    return found != type_list[subsystem.getSubsystem()].end();
}

int TypeRegistry::getLevelOfType(Subsystem subsystem,
    const std::string &type) {
    
    return type_list[subsystem.getSubsystem()][type];
}

}  // namespace Log
}  // namespace Crystallizer
