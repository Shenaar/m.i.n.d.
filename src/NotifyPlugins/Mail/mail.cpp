#include "../../Message.h"
#include "../../Config.h"
#include "MailThread.h"
#include <string>

using namespace std;

string to;
string subject;

extern "C"
bool init(Config *conf) {
    to = conf->getStringValue("mail.to");
    subject = conf->getStringValue("mail.subject", "Notice from M.I.N.D.");    
    if (to == "") {
        return false;
    }
    return true;
}

extern "C"
const char *getName(void) {
    return "mail";
}

extern "C"
bool notify(Message *msg) {
    Mail *mail = new Mail;
    mail->to = to;
    mail->subject = subject;
    mail->message = msg->getText();
    pthread_t tid;
    pthread_create(&tid, NULL, sendMail, (void*)mail);
    return true;
}

