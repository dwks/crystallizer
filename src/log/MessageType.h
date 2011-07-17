#ifndef SERIALIZER_LOG__MESSAGE_TYPE_H
#define SERIALIZER_LOG__MESSAGE_TYPE_H

#include <string>

#include "Subsystem.h"
#include "VerbosityLevel.h"

namespace Crystallizer {
namespace Log {

class MessageType {
private:
    Subsystem subsystem;
    std::string type;
public:
    MessageType(Subsystem subsystem);
    MessageType(Subsystem subsystem, const std::string &type);
    
    bool showUnder(const VerbosityLevel &level);
    
    Subsystem getSubsystem() const;
    std::string getType() const;
    
    int getLevel() const;
    std::string getDescription() const;
};

}  // namespace Log
}  // namespace Crystallizer

#endif
