#ifndef DAEMON_H
#define DAEMON_H

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h> 
#include <errno.h> 
#include <sys/resource.h>
#include "Log.h"

class Daemon {

public:
    Daemon(void);
    ~Daemon(void);
    // Инициализация демона 
    int init(sighandler_t fsignal, bool single_mode); 
    // Вызывается при остановке демона
    void deinit(void); 
private:
    // Установка блокировки на файл по дескриптору
    int lockfile(int fd);
    // Установка блокировки на файл по его имени
    bool lock(const char* name);
    int n;
};
#endif
