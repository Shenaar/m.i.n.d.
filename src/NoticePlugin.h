#ifndef NoticePlugin_H
#define NoticePlugin_H

#include "Library.h"
#include "Log.h"
#include "Config.h"
#include "Message.h"

#include <map>
#include <set>

using namespace std;

enum PriorityType {
    ANY,
    LIST
};

class NoticePlugin : public Library {
public:
    NoticePlugin(const char *filename);
    bool notify(Message *message);
    const char *getName(void);
    bool mustSend(MessageType type);
private:
    const char *name;
    typedef bool (*NotifyFunction)(Message*);
    typedef const char* (*NameFunction)();
    typedef bool (*InitFunction)(Config*);
    NotifyFunction notifyFunction;
    
    set<MessageType> priority;
    PriorityType priorityType;
};

#endif
