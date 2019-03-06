#ifndef _NotifyBot_H
#define _NotifyBot_H

#include <gloox/client.h>
#include <gloox/jid.h>
#include <gloox/message.h>
#include <gloox/connectionlistener.h>

#include "../../Thread.h"
#include "../../Mutex.h"

class NotifyBot : public gloox::ConnectionListener, Thread {
public:
    NotifyBot(std::string user, std::string pass, std::string receiver);
    
    bool sendMessage(std::string message);
    
    virtual void onConnect(void);
    virtual void onDisconnect(gloox::ConnectionError e);
    virtual bool onTLSConnect(const gloox::CertInfo &c);
    
private:
    gloox::Client *client;
    
    virtual void *work(void *arg);
    Mutex *lock;
    
    std::string user;
    std::string pass;
    std::string receiver;
};

#endif

