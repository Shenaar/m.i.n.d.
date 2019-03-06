#include "MessageDispatcher.h"

MessageDispatcher::MessageDispatcher(void) {  
    vector<string> names = sConfig->getListValue("NotifyPlugins");
    vector<string>::iterator iter = names.begin();
    for (; iter != names.end(); ++iter) {
        NoticePlugin *plugin = NULL;
        string filename = *iter + ".so";
        try {
            plugin = new NoticePlugin(filename.c_str());
        } catch (char *error) {
            sLog->write(LOG_ERR, "Library error: %s.", error);
            delete plugin;
            continue;
        }
        plugins.push_back(plugin);
    }
}

void *MessageDispatcher::work(void *arg) {
    while (true) {
        Message *msg = sQueue->dequeue();        
        if (msg == NULL) {
            return NULL;
        }
        dispatch(msg);
        delete msg;
    }
    return NULL;
}

void MessageDispatcher::dispatch(Message *msg) {
    list<NoticePlugin*>::iterator iter = plugins.begin();
    for (; iter != plugins.end(); ++iter) {
        NoticePlugin *plugin = *iter;
        if (!plugin->mustSend(msg->getType())) {
            continue;
        }
        if (!plugin->notify(msg)) {
            sLog->write(LOG_ERR, "Can't notify with plugin %s. Logging message here.", plugin->getName());
            sLog->writeMessage(msg);  
        }      
    }
}

MessageDispatcher::~MessageDispatcher(void) {
    sQueue->terminate();
    list<NoticePlugin*>::iterator iter = plugins.begin();
    for (; iter != plugins.end(); ++iter) {
        delete *iter;       
    }    
    plugins.clear();
}

