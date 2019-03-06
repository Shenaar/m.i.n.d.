#ifndef _MailThread_H
#define _MailThread_H

#include <string>
#include <pthread.h>

using namespace std;

struct Mail {
    string to;
    string subject;
    string message;
};

void *sendMail(void *arg);

#endif
