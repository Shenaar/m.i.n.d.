#include "../../Message.h"
#include "../../Config.h"
#include <stdio.h>
#include <string>
#include <map>
#include <time.h>
using namespace std;

FILE *out = NULL;

extern "C"
bool init(Config *conf) {
    string filename = conf->getStringValue("dummy.filename");
    if (filename == "") {
        return false;
    }
    out = fopen(filename.c_str(), "a+");
    return out != NULL;
}

extern "C"
const char *getName(void) {
    return "dummy";
}

extern "C"
bool notify(Message *msg) {
    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    char buf[20] = {0};
    snprintf(buf, 20, "%d-%d-%d_%d-%d-%d", 
            aTm->tm_year + 1900, aTm->tm_mon + 1, aTm->tm_mday,
            aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
    fprintf(out, "[%s]%s\n", buf, msg->getText().c_str());
    fflush(out);
    return true;
}
