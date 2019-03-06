#include "MonitoringProcess.h"

MonitoringProcess::MonitoringProcess(map<string, pid_t> *observedList,map<string, int> priority, unsigned sleep_time, BlockedQueue<Message*>* queue):observedList(observedList),priority(priority),sleep_time(sleep_time),queue(queue)
{ }

void MonitoringProcess::updateObservedList(void)
{
    bool flag = false;
    updateProcessList();
    std::map<string, pid_t>::iterator pos;
    for(pos = this->observedList->begin();pos!=this->observedList->end();++pos)
    {
        flag = false;
        for(int i=0;i<this->processList.size();++i)
        {
            if(pos->first == this->processList[i]->name)
            {
                flag = true; 
                if(pos->second == (pid_t)NULL)
                {
                    pos->second = this->processList[i]->pid;
                } 
                else if(pos->second != this->processList[i]->pid)
                {
                    handlerChanhes(pos->first);
                    pos->second = this->processList[i]->pid;
                }
            }
        }
        if(flag == false && pos->second != (pid_t)NULL)
        {
            handlerChanhes(pos->first);            	
            pos->second = (pid_t)NULL;
        }
    }
}

void MonitoringProcess::updateProcessList(void)
{
    processList.clear();
    
    if (chdir ("/proc") != 0)
       return;
    
    DIR *dp = NULL;
    if ((dp = opendir (".")) == NULL)
       return;

    
    dirent *dirp = NULL;
    while ((dirp = readdir (dp)) != NULL)
    {
       istringstream iss (dirp->d_name);
 
       int num = 0;
       if (! (iss >> num))
           continue;
 
       Process *process = new Process;
       if (getProcessInfo (dirp->d_name, process))
           processList.push_back(process);
       else
           delete process;
    }
 
    closedir (dp);
}

bool MonitoringProcess::getProcessInfo(const char *dir_name, Process *proc)
{
    string path (dir_name);
    path.append ("/stat");
 
    ifstream ifs (path.c_str());
    if (! ifs.is_open())
       return false;

 
    ifs >> proc->pid >> proc->name >> proc->state >> proc->ppid;
    ifs.close();
	
    proc->name = proc->name.substr(1, proc->name.size()-2);
    return true;
}

int MonitoringProcess::handlerChanhes(string str)
{
    char msg[512]={0};
    snprintf(msg, sizeof(msg), "Process %s dies.", str.c_str());
    queue->enqueue(new Message((MessageType)this->priority[str], msg));
    return 0;
}

void* MonitoringProcess::work(void* arg)
{
	while(true)
	{			
		updateObservedList();
		sleep(sleep_time);
	}
    return NULL;
}

