#ifndef SERIALIZER_LOG__SUBSYSTEM_H
#define SERIALIZER_LOG__SUBSYSTEM_H

#include <string>

namespace Crystallizer {
namespace Log {

class Subsystem {
public:
    enum SubsystemType {
        GLOBAL,
        NETWORK,
        FRACTAL,
        SUBSYSTEMS
    };
private:
    SubsystemType subsystem;
public:
    Subsystem(SubsystemType subsystem);
    
    SubsystemType getSubsystem() const;
    
    std::string getDescription() const;
    std::string getDescription(const std::string &type) const;
};

}  // namespace Log
}  // namespace Crystallizer

#endif
