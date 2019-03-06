#include "Thread.h"

Thread::Thread(void):stillAlive(NULL),isRun(false) {}

int Thread::start(void)
{
   return pthread_create( &id, NULL, svc, (void*)this); 
}

int Thread::stop(void)
{
    pthread_cancel(id);
}

bool Thread::getIsRun(void)
{
    return isRun;  
}

void Thread::setStillAlive(sem_t* sem)
{
    stillAlive = sem;
}

void Thread::handlersDeath(void* arg)
{
    Thread* _this = (Thread*)arg;
    _this->isRun = false;
    if(_this->stillAlive != NULL)
        sem_post(_this->stillAlive);
}

void* Thread::svc(void* arg)
{
    Thread* _this = (Thread*)arg;
    pthread_cleanup_push(handlersDeath, arg);
    _this->isRun = true;
    _this->work(NULL);    
    pthread_cleanup_pop(0);        
}

void Thread::join(void) {
    pthread_join(id, NULL);    
}
