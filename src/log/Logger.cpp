#include "Logger.h"

namespace Crystallizer {
namespace Log {

Logger Logger::instance;

void Logger::closeAllStreams() {
    for(stream_list_t::iterator it = streamList.begin();
        it != streamList.end(); ++ it) {
        
        delete *it;
    }
}

void Logger::addStream(Stream *stream) {
    streamList.push_back(stream);
}

void Logger::log(const Message &message) {
    for(stream_list_t::iterator it = streamList.begin();
        it != streamList.end(); ++ it) {
        
        Stream *stream = *it;
        
        if(message.getType().showUnder(stream->getLevel())) {
            stream->write(message.asText(stream->isWideStream()));
        }
    }
}

}  // namespace Log
}  // namespace Crystallizer
