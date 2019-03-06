#ifndef OVERSEER_H
#define OVERSEER_H

#include <semaphore.h>
#include <unistd.h>
#include <vector>
#include "Thread.h"
#include "Log.h"

using std::vector;

class Overseer : public Thread
{
private:
    
    unsigned countThread;
    sem_t* stillAliveThreads;
    vector<Thread*>* threads;
    virtual void* work(void* arg);
   
public:
    
    Overseer(void);
    virtual ~Overseer(void);
    virtual int stop(void);
    void addThread(Thread* thread);
};

#endif
