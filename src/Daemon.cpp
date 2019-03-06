#include "Daemon.h"
 

Daemon::Daemon(void) {
}

int Daemon::init(sighandler_t fsignal, bool single_mode)
{
    pid_t pid, sid;
    struct rlimit rl;
    struct sigaction sa;          
    
    //Сбросить маску режима создания файла    
    umask(0);

    //Получить максимально возможный номер дескриптора файла
    if( getrlimit( RLIMIT_NOFILE, &rl) < 0)
    {
        sLog->write( LOG_ERR, "Error:\tgetrlimit()\n");
        return 1;
    }
        
    //Стать лидером новой сессии, чтобы утратить управляющий терминал
    if( (pid = fork()) < 0)
    {
        sLog->write( LOG_ERR, "Error:\tfork()\n");
        return 1;
    }
    else if( pid != 0)
        return 1;
          
    if( (sid = setsid()) < 0)
    {
        sLog->write(LOG_ERR, "Error:\tsetsid()\n");
        return 1;
    }
    
    //Обеспечить невозможность обретения управляющего терминала в будущем
    sa.sa_handler =  SIG_IGN;
    sigemptyset( &sa.sa_mask);
    if( sigaction(SIGHUP, &sa, NULL) < 0)
    {
        sLog->write(LOG_ERR, "Error:\tsigaction()\n");
        return 1;
    }    
    if( (pid = fork()) < 0)
    {
        sLog->write(LOG_ERR, "Error:\tfork()\n");
        return 1;
    }
    else if( pid != 0)
        return 1; 
    
    //Назначить корневой каталок текущим рабочим, чтобы отмонтировать фс
    if( chdir("/") < 0)
    {
        sLog->write(LOG_ERR, "Error:\tchdir()\n");
        return 1;
    }
    
    //Закрываем все открытые файловые дескрипторы
    if( rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for( int i=0;i<rl.rlim_max; ++i)
        close(i);
    
    //Присоединяем файловые дескрипторы 0, 1 и 2 к /dev/null
    int fd0 = open( "/dev/null", O_RDWR);
    int fd1 = dup(0);
    int fd2 = dup(0);
    
    
    if( fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
        sLog->write(LOG_ERR, "Error:\tfd is not null\n");
        return 1;
    }
    
    //настраиваем обработчиком всех сигналов функцию fsignal
    for( int i=1; i<32; ++i)
        signal(i,fsignal);
        
    if(single_mode == true && Daemon::lock("mind") == false)
    {
        sLog->write(LOG_ERR, "нет прав на запуск/демон уже запущен"); 
        return 1; 
    } else 
    {
        sLog->write(LOG_INFO, "running");   
        return 0;
    }
}

bool Daemon::lock(const char* name)
{
    int fd;
    char buf[16] = {0};
    char filename[64] = {0};
    
    snprintf(filename, sizeof(filename), "/var/run/%s.pid", name); 
    
    fd = open(filename, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); 
    if (fd < 0)
    { 
        sLog->write(LOG_ERR, "не возможно открыть %s: %s", filename, strerror(errno)); 
        return false; 
    }
     
    if (lockfile(fd) < 0)
    { 
        if (errno == EACCES || errno == EAGAIN)
        { 
            close(fd); 
            return false; 
        }   
        sLog->write(LOG_ERR, "невозможно установить блокировку на %s: %s", filename, strerror(errno)); 
        return false; 
    } 
    
    ftruncate(fd, 0); 
    snprintf(buf, sizeof(buf), "%ld", (long)getpid()); 
    write(fd, buf, strlen(buf)+1); 
    return true; 
}

int Daemon::lockfile(int fd)
{
    flock fl; 
    fl.l_type = F_WRLCK; 
    fl.l_start = 0;  
    fl.l_whence = SEEK_SET; 
    fl.l_len = 0; 
    return fcntl(fd, F_SETLK, &fl); 
}

void Daemon::deinit(void) {
    unlink("/var/run/mind.pid");
}

Daemon::~Daemon(void) {

}

