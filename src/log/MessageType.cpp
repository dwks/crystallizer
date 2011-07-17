#include "MessageType.h"

namespace Crystallizer {
namespace Log {

MessageType::MessageType(Subsystem subsystem)
    : subsystem(subsystem), type() {
    
}

MessageType::MessageType(Subsystem subsystem, const std::string &type)
    : subsystem(subsystem), type(type) {
    
}

bool MessageType::showUnder(const VerbosityLevel &level) {
    return getLevel() <= level.getLevel(subsystem);
}

Subsystem MessageType::getSubsystem() const {
    return subsystem;
}

std::string MessageType::getType() const {
    return type;
}

int MessageType::getLevel() const {
    return -1;
}

std::string MessageType::getDescription() const {
    return subsystem.getDescription(type);
}

}  // namespace Log
}  // namespace Crystallizer
