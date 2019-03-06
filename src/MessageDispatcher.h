#ifndef MessageDispatcher_H
#define MessageDispatcher_H

#include "Thread.h"
#include "Log.h"
#include "Config.h"
#include "Library.h"
#include "Message.h"
#include "BlockedQueue.h"
#include "NoticePlugin.h"

#include <list>
#include <string>
#include <vector>

using namespace std;

class MessageDispatcher : public Thread {    
public:
    MessageDispatcher(void);
    ~MessageDispatcher(void);
    
private:    
    virtual void *work(void *arg);
    void dispatch(Message *message);
    
    list<NoticePlugin*> plugins;
    
    
};

#endif
