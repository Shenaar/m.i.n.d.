#ifndef _LOG_H_
#define _LOG_H_

#include <string>

#include <syslog.h>

#include "Singleton.h"
#include "Message.h"
#include "Mutex.h"

using namespace std;

class Log : public Singleton<Log> {
public:
    void write(int priority, char const *format, ...);
    void writeMessage(Message *message);    

    ~Log(void);

    friend class Singleton<Log>;
private:
    Log(void);
    Mutex lock;
};

#define sLog Log::instance()

#endif // _LOG_H_
