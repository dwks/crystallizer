#ifndef CRYSTALLIZER_LOG__ABSTRACT_STREAM_H
#define CRYSTALLIZER_LOG__ABSTRACT_STREAM_H

#include "Stream.h"

namespace Crystallizer {
namespace Log {

class AbstractStream : public Stream {
private:
    VerbosityLevel level;
    bool isWide;
public:
    AbstractStream(VerbosityLevel level, bool isWide = true)
        : level(level), isWide(isWide) {}
    virtual ~AbstractStream() {}
    
    virtual VerbosityLevel getLevel() const { return level; }
    virtual bool isWideStream() const { return isWide; }
    
    virtual void write(const std::string &data) = 0;
};

}  // namespace Log
}  // namespace Crystallizer

#endif
