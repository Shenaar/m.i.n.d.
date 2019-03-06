#ifndef MONITORINGLOG_H
#define MONITORINGLOG_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <string>
#include <map>
#include "../../Thread.h"
#include "../../Message.h"
#include "../../BlockedQueue.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define DATA_LEN    256

using namespace std;
  
class MonitoringLog: public Thread
{
public:
    MonitoringLog(const char* target, map<string, int> priority, BlockedQueue<Message*>* queue);
    //~MonitoringLog(void);
    
private:
    const char* target;
    map<string, int> priority;
    BlockedQueue<Message*>* queue;
    
    virtual void* work(void* arg);
    int handlerChanhes(string str);
    
};

#endif
