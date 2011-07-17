#include "Subsystem.h"
#include "TypeRegistry.h"

namespace Crystallizer {
namespace Log {

Subsystem::Subsystem(SubsystemType subsystem) : subsystem(subsystem) {
    
}

Subsystem::SubsystemType Subsystem::getSubsystem() const {
    return subsystem;
}

std::string Subsystem::getDescription() const {
    static const char *descriptions[] = {
        "GLOBAL",
        "NETWORK",
        "FRACTAL"
    };
    int size = static_cast<int>(sizeof(descriptions) / sizeof(*descriptions));
    
    if(subsystem >= 0 && subsystem < size) {
        return descriptions[subsystem];
    }
    else {
        return "???";
    }
}

std::string Subsystem::getDescription(const std::string &type) const {
    if(type.length() == 0) {
        return getDescription();
    }
    else if(TypeRegistry::getInstance().isValidType(subsystem, type)) {
        return getDescription() + "::" + type;
    }
    else {
        return "***INVALID_TYPE***";
    }
}

}  // namespace Log
}  // namespace Crystallizer
