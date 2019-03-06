#ifndef MONITORINGPLUGINS_H
#define MONITORINGPLUGINS_H

#include "BlockedQueue.h"
#include "Overseer.h"
#include "Library.h"
#include "Config.h"
#include "Log.h"
#include <string>
#include <list>
#include <map>

using namespace std;
 
class MonitoringPlugins : public Overseer
{
private:
    vector<Library* > plugins;
    typedef Thread* (*InstanceFunction)(BlockedQueue<Message*>*);
    typedef bool (*InitFunction)(map<string, string>);

public:
    MonitoringPlugins(void);
    ~MonitoringPlugins(void);
       
};

#endif
