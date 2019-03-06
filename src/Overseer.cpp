#include "Overseer.h"

Overseer::Overseer(void)
{
    countThread = 0;
    stillAliveThreads = new sem_t();
    threads = new vector<Thread*>();
}

void Overseer::addThread(Thread* thread)
{
    threads->push_back(thread);
    thread->setStillAlive(stillAliveThreads);
    ++countThread;    
}

void* Overseer::work(void* arg)
{
    sem_init(stillAliveThreads, 0, countThread);     
        
    while(true)
    {
        for(int i=0;i<threads->size();++i)
        {
            if((*threads)[i]->getIsRun() == false)
            {
                sem_wait(stillAliveThreads);
                (*threads)[i]->start();    
            }
        }        
        sem_wait(stillAliveThreads);
        sem_post(stillAliveThreads);
    }
    
}

int Overseer::stop(void)
{
    this->Thread::stop();
    for(int i=0;i<threads->size();++i)
    {
        threads->at(i)->stop();
    }    
}

Overseer::~Overseer(void) {
    this->stop();
    for(int i=0;i<threads->size();++i)
    {
        delete threads->at(i);
    }        
    delete threads;
}
