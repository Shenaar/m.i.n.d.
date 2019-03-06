#ifndef BLOCKED_QUEUE_H
#define BLOCKED_QUEUE_H

#include <queue>
#include "Mutex.h"

#define sQueue  Singleton<BlockedQueue<Message*> >::instance()   

using std::queue;

template<class T>
class BlockedQueue{
private:
    queue<T> q;
    Mutex pop_push;
    Mutex empty;   
    
public:
    BlockedQueue(void);
    void terminate(void);

    void enqueue(T val);
    T dequeue(void);

};

template<class T>
BlockedQueue<T>::BlockedQueue(void) 
{
    empty.lock();
}

template<class T>
void BlockedQueue<T>::enqueue(T val)
{
    pop_push.lock();
    q.push(val);
    if(q.size() == 1)
        empty.unlock();
    pop_push.unlock();
}

template<class T>
T BlockedQueue<T>::dequeue(void)
{
    if(q.empty() == true)
        empty.lock();
        
    pop_push.lock();
    
    T ret = (T)NULL;
    if(q.empty() == false)
    {
        ret = q.front();
        q.pop();
    }
    
    pop_push.unlock();
    return ret;
}

template<class T> 
void BlockedQueue<T>::terminate(void) 
{
    empty.unlock();
    pop_push.unlock();
}

#endif
