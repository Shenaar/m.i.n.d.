#include "Log.h"
#include "Config.h"
#include <stdio.h>
#include <stdarg.h>

Log::Log() {	
    openlog("m.i.n.d.", LOG_PID | LOG_CONS, LOG_USER);
}

void Log::write(int priority, char const *format, ...) {
    lock.lock();    
    va_list va;
    va_start(va, format);
    vsyslog(priority, format, va);
    va_end(va);
    lock.unlock();
}

void Log::writeMessage(Message *message) {
    lock.lock();
    syslog(LOG_INFO, "[%d]%s", message->getType(), message->getText().c_str());
    lock.unlock();
}

Log::~Log(void) {
    lock.lock();
    closelog();
    lock.unlock();
}
