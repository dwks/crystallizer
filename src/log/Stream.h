#ifndef SERIALIZER_LOG__STREAM_H
#define SERIALIZER_LOG__STREAM_H

#include <string>
#include "VerbosityLevel.h"

namespace Crystallizer {
namespace Log {

class Stream {
public:
    virtual ~Stream() {}
    
    virtual VerbosityLevel getLevel() const = 0;
    virtual bool isWideStream() const = 0;
    
    virtual void write(const std::string &data) = 0;
};

}  // namespace Log
}  // namespace Crystallizer

#endif
