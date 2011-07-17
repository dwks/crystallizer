#ifndef CRYSTALLIZER_NETWORK__DATA_RECEIVER_H
#define CRYSTALLIZER_NETWORK__DATA_RECEIVER_H

#include <string>

namespace Crystallizer {
namespace Network {

/** Observer for data received on a ClientSocket.
*/
class DataReceiver {
public:
    virtual ~DataReceiver() {}
    
    /** Return false to abort receive() calls to subsequent observers.
    */
    virtual bool receive(const std::string &data) = 0;
};

}  // namespace Network
}  // namespace Crystallizer

#endif
