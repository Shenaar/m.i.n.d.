#ifndef MESSAGE_GENERATOR_H
#define MESSAGE_GENERATOR_H

#include "Log.h"
#include "Thread.h"
#include "Message.h"
#include "BlockedQueue.h"
#include "Singleton.h"
#include <stdlib.h>
#include <stdio.h>

class MessageGenerator: public Thread
{
private:
    virtual void* work(void* arg);
    
public:
    MessageGenerator(void);
        
};
#endif

