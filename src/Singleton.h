#ifndef SINGLETONE_H
#define SINGLETONE_H

#include <stdlib.h>
#include "Mutex.h"

template<class T>
class Singleton
{
public:
    static T* instance(void);
    
protected:
    Singleton(void){};
    
private:
    static T* _instance; 
    static Mutex lock;   
};

template<class T>
Mutex Singleton<T>::lock;

template<class T>
T* Singleton<T>::_instance = NULL;

template<class T>
T* Singleton<T>::instance(void)
{
    lock.lock();
    if(_instance == NULL)
        _instance = new T();
    lock.unlock();
    return _instance;
}

#endif
