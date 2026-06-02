#include "Message.h"
#include <iostream>

Message::Message(std::string messenger, bool status, std::string content) {
	this->messenger = messenger;
	this->status = status;
	this->messageContent = content;
}

std::string Message::getMessenger() const {
	return this->messenger;
}

bool Message::getStatus() const {
	return this->status;
}

std::string Message::getMessageContent() const {
	return this->messageContent;
}

void Message::markAsRead() {
	this->status = true;
}

void Message::saveMessage(std::fstream& file) const {
	file << messenger << "\n" << std::to_string(status) << "\n" << messageContent << "\n";
}