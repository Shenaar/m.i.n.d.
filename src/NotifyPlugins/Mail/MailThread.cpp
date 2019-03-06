#include "MailThread.h"
#include <stdio.h>


void *sendMail(void *arg) {
    Mail *mail = (Mail*)arg;
    string name = "mail " + mail->to + " -s \"" + mail->subject + "\"";
    FILE *pipe = popen(name.c_str(), "w");
    if (pipe == NULL) {
        return false;
    }
    if(fprintf(pipe, "M.I.N.D. message: %s\n", mail->message.c_str()) < 0) {
        fclose(pipe);
        return false;
    }
    fflush(pipe);
    fclose(pipe);
    delete mail;
    return NULL;
}
