#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex
{
private:
    pthread_mutex_t mutex;

public:    
    Mutex(void);    
    ~Mutex(void);
    
    int lock(void);    
    int trylock(void);    
    int unlock(void);
        
};

#endif
