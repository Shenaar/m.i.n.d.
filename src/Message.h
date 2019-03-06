#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>

using namespace std;

typedef int MessageType;

class Message {
public:
	Message(const MessageType type, const string text);
	MessageType getType(void) const;
	string getText(void) const;
private:
	const MessageType type;
	const string text;
};

#endif // _MESSAGE_H_
