#ifndef SERIALIZER_LOG__MESSAGE_H
#define SERIALIZER_LOG__MESSAGE_H

#include <string>
#include <ctime>

#include "MessageType.h"

namespace Crystallizer {
namespace Log {

/** Represents a log message, with a type and a timestamp.
*/
class Message {
private:
    MessageType type;
    std::string text;
    std::time_t timestamp;
public:
    Message(MessageType type, const std::string &text);
    
    MessageType getType() const { return type; }
    
    /** Converts this message into a string representation. If @a allData is
        true, then this includes all of the information about the message
        (type, text, timestamp). But if @a allData is false, the representation
        is optimized to use as little horizontal space on the screen as
        possible.
    */
    std::string asText(bool allData = true) const;
};

}  // namespace Log
}  // namespace Crystallizer

#endif
