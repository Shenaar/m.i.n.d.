#ifndef _LIBRARY_H_
#define _LIBRARY_H_

class Library {
public:
	Library(const char *filename);
	virtual ~Library(void);
	void unload(void);
	void *getSymbol(const char *symbol);
private:
	void *handle;
};

#endif