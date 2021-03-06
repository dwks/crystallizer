#include "FileStream.h"

namespace Crystallizer {
namespace Log {

FileStream::FileStream(VerbosityLevel level, const char *filename)
    : AbstractStream(level) {
        
    stream.open(filename);
}

void FileStream::write(const std::string &data) {
    stream << data;
    stream.flush();
}

}  // namespace Log
}  // namespace Crystallizer
