#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <semaphore.h>

class Thread
{
private:

    pthread_t id;
    sem_t* stillAlive;
    bool isRun;
    static void* svc(void* arg);
    virtual void* work(void* arg) = 0;
    static void handlersDeath(void* arg);

public:

    Thread(void);   
    virtual int start(void);
    virtual int stop(void);
    
    void join(void);
    
    bool getIsRun(void);
    void setStillAlive(sem_t* sem); 
};

#endif
