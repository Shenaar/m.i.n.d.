#include "NotifyBot.h"
#include <string>
#include <stdio.h>

NotifyBot::NotifyBot(std::string user, std::string pass, std::string receiver) : lock(new Mutex()) {
    this->user = user;
    this->pass = pass;
    this->receiver = receiver;
    this->start();
}

bool NotifyBot::sendMessage(std::string message) {
    lock->lock();
    gloox::JID to = gloox::JID(receiver);
    gloox::Message::MessageType type = (gloox::Message::MessageType)1;
    gloox::Message msg(type, to, message);
    client->send(msg);
    lock->unlock();
    return true;
}

void NotifyBot::onConnect(void) {
    gloox::JID to = gloox::JID(receiver);
    gloox::Message::MessageType type = (gloox::Message::MessageType)1;
    std::string message = "Connected";
    gloox::Message msg(type, to, message);
    client->send(msg);
    lock->unlock();
}

void NotifyBot::onDisconnect(gloox::ConnectionError e) {
    return;
}

bool NotifyBot::onTLSConnect(const gloox::CertInfo &c) {
   return true;
}

void *NotifyBot::work(void *arg) {
    lock->lock();  
    this->client = new gloox::Client(user, pass);
    client->registerConnectionListener(this);
    this->client->connect();
    return NULL;
}
