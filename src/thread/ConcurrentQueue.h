#ifndef SERIALIZER_THREAD__CONCURRENT_QUEUE_H
#define SERIALIZER_THREAD__CONCURRENT_QUEUE_H

#include <queue>
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition_variable.hpp"

namespace Crystallizer {
namespace Thread {

/** A generic thread-safe queue. Both synchronous and asynchronous dequeuing
    are supported.
    
    Note: if this class is to be directly accessed from multiple threads, the
    object must be allocated on the heap and not on the stack.
*/
template <typename DataType>
class ConcurrentQueue {
private:
    std::queue<DataType> queue;
    boost::mutex mutex;
    boost::condition_variable condition;
public:
    /** Adds @a value to the queue. All existing elements will be dequeued from
        the queue before @a value is.
    */
    void enqueue(const DataType &value) {
        boost::mutex::scoped_lock lock(mutex);
        queue.push(value);
        lock.unlock();
        
        condition.notify_one();
    }
    
    /** Asynchronous dequeue. Returns true if an element was available in the
        queue, and sets @a value to this element.
    */
    bool tryDequeue(DataType &value) {
        boost::mutex::scoped_lock lock(mutex);
        if(queue.empty()) {
            return false;  // automatically unlocks the lock
        }
        
        value = queue.front();
        queue.pop();
        lock.unlock();
        
        return true;
    }
    
    /** Synchronous dequeue, which blocks until data is available.
    */
    void waitUntilDequeue(DataType &value) {
        boost::mutex::scoped_lock lock(mutex);
        while(queue.empty()) {
            condition.wait(lock);
        }
        
        value = queue.front();
        queue.pop();
    }
};

}  // namespace Thread
}  // namespace Crystallizer

#endif
