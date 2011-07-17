#ifndef SERIALIZER_LOG__ALIAS_STREAM_H
#define SERIALIZER_LOG__ALIAS_STREAM_H

#include <iosfwd>
#include "AbstractStream.h"

namespace Crystallizer {
namespace Log {

class AliasStream : public AbstractStream {
private:
    std::ostream &stream;
public:
    AliasStream(VerbosityLevel level, std::ostream &stream,
        bool wideStream = true);
    
    virtual void write(const std::string &data);
};

}  // namespace Log
}  // namespace Crystallizer

#endif
