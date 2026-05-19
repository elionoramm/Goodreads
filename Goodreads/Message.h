#pragma once
#include <string>
class Message {
	std::string messenger;
	bool status;
	std::string messageContent;
public:
	Message(std::string messenger, bool status, std::string content);
	std::string getMessenger() const;
	bool getStatus() const;
	std::string getMessageContent() const;
	void markAsRead();
};