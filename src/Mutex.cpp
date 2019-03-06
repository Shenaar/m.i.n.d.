#include "Mutex.h"

Mutex::Mutex(void)
{
    pthread_mutex_init(&mutex, NULL);
}

Mutex::~Mutex(void)
{
    pthread_mutex_destroy(&mutex);
}

int Mutex::lock(void)
{
    return pthread_mutex_lock(&mutex);
}

int Mutex::trylock(void)
{
    return pthread_mutex_trylock(&mutex);
}

int Mutex::unlock(void)
{
    return pthread_mutex_unlock(&mutex);
}
