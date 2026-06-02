#pragma once
#include <string>
#include <fstream>
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
	void saveMessage(std::fstream& file) const;
};