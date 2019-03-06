#include "../../Thread.h"
#include "../../Message.h"
#include "../../BlockedQueue.h"
#include "../../Config.h"
#include "MonitoringProcess.h"

#include <vector>
#include <map>
 
unsigned sleep_time = 0;
map<string, pid_t> *observedList = NULL;
map<string, int> priority;

extern "C" bool init(Config *conf) 
{
    observedList = new map<string, pid_t>();
    
    sleep_time = conf->getIntValue("ScanProcess.time", 5);    
    vector<string> val = conf->getListValue("ScanProcess.targets");

    vector<string>::iterator iter = val.begin();
	for(;iter!=val.end();++iter)
	{
		size_t first = (*iter).rfind("[");
		size_t last = (*iter).rfind("]");
		if(first != string::npos && last != string::npos && (last-first)>=2 )
		{			
			string str = (*iter).substr(first+1, last-first-1 );
			int number = atoi(str.c_str());			
			str = (*iter).substr(0,first);
			
			priority[str] = number;
			(*observedList)[str] = (pid_t)NULL;
		} else
		{
			return false;
		}
	}    
    
    if (sleep_time == 0 || observedList->size() == 0 || priority.size() == 0) {
        return false;
    } 
    return true; 
}

extern "C" Thread* instance(BlockedQueue<Message*>* queue)
{
    return new MonitoringProcess(observedList, priority, sleep_time, queue);
}

