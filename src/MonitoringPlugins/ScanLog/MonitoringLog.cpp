#include "MonitoringLog.h"

MonitoringLog::MonitoringLog(const char* target, map<string, int> priority, BlockedQueue<Message*>* queue):target(target),priority(priority),queue(queue)
{ }

void* MonitoringLog::work(void* arg)
{
    int length, fd, wd;
    char buffer[BUF_LEN];
    char data[DATA_LEN] = {0};
    FILE* htarget;                
    
    if( (htarget = fopen(this->target,"r")) == NULL)
        return NULL;
            
    if( fseek(htarget, -1, SEEK_END) == -1)
        return NULL;
    
    if( (fd = inotify_init()) < 0)
        return NULL;

    wd = inotify_add_watch( fd, this->target, IN_MODIFY | IN_CREATE | IN_DELETE );
    
    while(true)
    {
        
        int i = 0;
        if( (length = read( fd, buffer, BUF_LEN )) < 0)
            return NULL;    
        
        while ( i < length ) 
        {
            
            string str = "";
            inotify_event *event = ( inotify_event * ) &buffer[ i ];
            
            if ( event->mask & IN_MODIFY) 
            {
                while('\0' != fgets(data, DATA_LEN, htarget))
                {
                    str+=data;
                    memset( (void*)data, 0, DATA_LEN);
                }
                fseek(htarget, -1, SEEK_END);
                this->handlerChanhes(str);
            }                           
            i += EVENT_SIZE;
        }
    }         
  
    inotify_rm_watch( fd, wd );
    close( fd );    
}

int MonitoringLog::handlerChanhes(string str)
{
    map<string, int>::iterator iter = priority.begin();
	for(;iter!=priority.end();++iter)
	{
		if( str.find((*iter).first.c_str()) != string::npos)
        {
            char msg[512]={0};
            snprintf(msg, sizeof(msg), "Alert! Match is found: %s", (*iter).first.c_str());
            queue->enqueue(new Message((MessageType)(*iter).second, msg));
        }
    }    
    return 0;
}
    
