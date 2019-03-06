#include "Library.h"
#include <dlfcn.h>
#include <stdlib.h>
#include "Log.h"

Library::Library(const char *filename) {
    this->handle = dlopen(filename, RTLD_LAZY);
    if (this->handle == NULL) {
        throw dlerror();
    }
}

Library::~Library(void) {
    this->unload();
}

void Library::unload(void) {
    if (dlclose(this->handle) != 0) {
        sLog->write(LOG_ERR, "Library error: can't unload library %s.", dlerror());
    }	
}

void *Library::getSymbol(const char *symbol) {
    if (this->handle == NULL) {
        return NULL;
    }		
    void *res = dlsym(this->handle, symbol);
    return res;
}
