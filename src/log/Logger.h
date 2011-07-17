#ifndef SERIALIZER_LOG__LOGGER_H
#define SERIALIZER_LOG__LOGGER_H

#include <vector>

#include "Stream.h"
#include "Message.h"
#include "misc/StreamAsString.h"

namespace Crystallizer {
namespace Log {

class Logger {
private:
    static Logger instance;
public:
    static Logger &getInstance() { return instance; }
private:
    typedef std::vector<Stream *> stream_list_t;
    stream_list_t streamList;
public:
    /** The Logger takes ownership of @a stream and will delete it when
        necessary.
    */
    void addStream(Stream *stream);
    void closeAllStreams();
    
    void log(const Message &message);
};

}  // namespace Log
}  // namespace Crystallizer

#define LOG(subsystem, text) \
    ::Crystallizer::Log::Logger::getInstance().log( \
        ::Crystallizer::Log::Message( \
            ::Crystallizer::Log::MessageType( \
                ::Crystallizer::Log::Subsystem::subsystem), \
            ::Crystallizer::Misc::StreamAsString() << text))

#define LOG2(subsystem, type, text) \
    ::Crystallizer::Log::Logger::getInstance().log( \
        ::Crystallizer::Log::Message( \
            ::Crystallizer::Log::MessageType( \
                ::Crystallizer::Log::Subsystem::subsystem, \
                # type), \
            ::Crystallizer::Misc::StreamAsString() << text))

#endif
