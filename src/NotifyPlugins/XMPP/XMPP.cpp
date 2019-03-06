#include "../../Message.h"
#include "../../Config.h"
#include "NotifyBot.h"

#include <string>
#include <map>

using namespace std;

NotifyBot *bot = NULL;

extern "C"
bool init(Config *conf) {
    string user = conf->getStringValue("XMPP.username");
    string pass = conf->getStringValue("XMPP.password");
    string to =   conf->getStringValue("XMPP.to");
    if (user == "" || pass == "" || to == "") {
        return false;
    }
    bot = new NotifyBot(user, pass, to);
    return true;    
}

extern "C"
const char *getName(void) {
    return "XMPP";
}

extern "C"
bool notify(Message *msg) {
    if (bot != NULL) {
        bot->sendMessage(msg->getText());
        return true;
    }
    return false;
}

