#ifndef MONITORINGPROCESS_H
#define MONITORINGPROCESS_H

#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "../../Thread.h"
#include "../../Message.h"
#include "../../BlockedQueue.h"


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
 
using namespace std;
 
struct Process
{
    pid_t pid;
    pid_t ppid;
    char state;
    std::string name;
};

class MonitoringProcess: public Thread
{
public:
    MonitoringProcess(map<string, pid_t> *observedList, map<string, int> priority, unsigned sleep_time, BlockedQueue<Message*>* queue);

private:    
    BlockedQueue<Message*>* queue;
    vector<Process*> processList;
    map<string, pid_t> *observedList;
    map<string, int> priority;     
    unsigned sleep_time;
	
    void updateProcessList(void);
    void updateObservedList(void);
    bool getProcessInfo (const char *filename, Process *proc);
    int handlerChanhes(string str);
    
    virtual void* work(void* arg);
};

#endif
