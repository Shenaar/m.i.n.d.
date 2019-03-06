#include "../../Thread.h"
#include "../../Message.h"
#include "../../BlockedQueue.h"
#include "../../Config.h"
#include "MonitoringLog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>

using std::map;
using std::vector;
using std::string;

string target = "";
map<string, int> priority;

extern "C" bool init(Config *conf) 
{
    target = conf->getStringValue("ScanLog.target");  
    vector<string> templates = conf->getListValue("ScanLog.templates");
        
    if (target == "" || templates.size() == 0) {
        return false;
    }
    
    vector<string>::iterator iter = templates.begin();
	for(;iter!=templates.end();++iter)
	{
		size_t first = (*iter).rfind("[");
		size_t last = (*iter).rfind("]");
		if(first != string::npos && last != string::npos && (last-first)>=2 )
		{			
			string str = (*iter).substr(first+1, last-first-1 );
			int number = atoi(str.c_str());			
			str = (*iter).substr(0,first);
			priority[str] = number;
		} else
		{
			return false;
		}
	}
	 
    return true;    
}

extern "C" Thread* instance(BlockedQueue<Message*>* queue)
{
    return new MonitoringLog(target.c_str(), priority, queue);
}

