#include "NoticePlugin.h"

NoticePlugin::NoticePlugin(const char *filename) : Library(filename) {
    NameFunction nf = (NameFunction) getSymbol("getName");
    InitFunction init = (InitFunction) getSymbol("init");
    notifyFunction = (NotifyFunction) getSymbol("notify");
    if (nf == NULL || notifyFunction == NULL || init == NULL) {
        sLog->write(LOG_ERR, "Bad plugin %s, %u, %u, %u", filename, nf, notifyFunction, init);
        return;
    }
    name = nf();
    if (!init(sConfig)) {
        sLog->write(LOG_ERR, "Error initializing plugin %s", name);
        return;
    }    
    
    string pluginName = name;
    int _priorityType = sConfig->getIntValue(pluginName + ".priorityType", -1);
    if (_priorityType == -1) {
        this->priorityType = ANY;
    } else {
        this->priorityType = LIST;
        vector<string> p = sConfig->getListValue(pluginName + ".priority");
        vector<string>::iterator iter = p.begin();
        for (; iter != p.end(); ++iter) {
            MessageType t = atoi(iter->c_str());
            priority.insert(t);
        }
    }
    
    sLog->write(LOG_NOTICE, "Plugin %s loaded", name);
}

bool NoticePlugin::notify(Message *msg) {
    if (notifyFunction == NULL) {
        return false;
    }
    return notifyFunction(msg);
}

bool NoticePlugin::mustSend(MessageType type) {
    return priorityType == ANY || priority.count(type) != 0;
}

const char *NoticePlugin::getName(void) {
    return name;
}
