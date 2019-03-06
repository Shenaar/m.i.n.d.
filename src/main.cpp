#include "Log.h"
#include "Daemon.h"
#include "Overseer.h"
#include "MessageDispatcher.h"
#include "MonitoringPlugins.h"

#include <stdio.h>
#include <errno.h>

Overseer* mainOverseer = NULL;

void fsignal(int sig)
{ 
    switch(sig)
    {
        case SIGTERM:
        case SIGINT:
        case SIGQUIT:
            sLog->write(LOG_NOTICE,"Stopped on signal %d",sig);
            mainOverseer->stop();
            break;
            
        case SIGSEGV:
            sLog->write(LOG_NOTICE,"Segmentation Fault");
            mainOverseer->stop();
            break;
            
        default:
            break;
    }
} 

int main(int argc, char *argv[]) {

    if (argc > 1 && strcmp(argv[1], "stop") == 0) {
        FILE *file = fopen("/var/run/mind.pid", "r");
        if (file == NULL) {
            printf("Невозможно открыть файл /var/run/mind.pid." 
                   " Возможно, M.I.N.D. не запущен.\n");
            return 1;
        }
        pid_t pid = 0;
        fscanf(file, "%d", &pid);
        printf("M.I.N.D. с pid = %d останавливается.\n", pid);
        int res = kill(pid, SIGTERM);
        if (res != 0) {
            printf("Ошибка остановки: %d.\n", errno);
        } else {
            printf("M.I.N.D. с pid = %d остановлен.\n", pid);
        }
        return 0;
    }
    
    
    Daemon daemon;
    if(daemon.init(fsignal, true) != 0)
        return 1;   
            
    mainOverseer = new Overseer();
    mainOverseer->addThread(new MessageDispatcher());
    mainOverseer->addThread(new MonitoringPlugins());
    mainOverseer->start();    
    
    mainOverseer->join();
    delete mainOverseer;
    daemon.deinit();
    return 0;
}
