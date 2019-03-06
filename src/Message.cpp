#include "Message.h"

Message::Message(const MessageType _type, const string _text) : type(_type), text(_text) {
}

MessageType Message::getType(void) const {
	return this->type;
}

string Message::getText(void) const {
	return this->text;
}
