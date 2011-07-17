#ifndef SERIALIZER_LOG__FILE_STREAM_H
#define SERIALIZER_LOG__FILE_STREAM_H

#include <fstream>
#include "AbstractStream.h"

namespace Crystallizer {
namespace Log {

class FileStream : public AbstractStream {
private:
    std::ofstream stream;
public:
    FileStream(VerbosityLevel level, const char *filename);
    
    virtual void write(const std::string &data);
};

}  // namespace Log
}  // namespace Crystallizer

#endif
