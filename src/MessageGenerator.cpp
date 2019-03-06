#include "MessageGenerator.h"

MessageGenerator::MessageGenerator(void)
{
}

void* MessageGenerator::work(void* arg)
{
    char buff[10]={0};
    
    while(true)
    {
        sleep(rand()%10);
        sprintf(buff, "%d\n", rand()%100);
        sQueue->enqueue(new Message(0, buff));
    }
    
    return NULL;
}
