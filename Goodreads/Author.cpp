#include <iostream>
#include "Author.h"
// visitor
void Author::accept(Visitor* visitor) const {
	visitor->visitAuthor(*this);
}

Author::Author(const std::string& username, const std::string& password) : Reader(username, password) {}

std::string Author::getUserType() const {
	return "Author";
}

void Author::help() const {
	std::cout << "register <username> <password> <userType>\n"
		"login <username> <password>\n"
		"logout\n"
		"exit\n"
		"search <name>\n"
		"follow <username>\n"
		"add-book <bookName> <status> <rating>*\n"
		"create-shelf <name>\n"
		"delete-shelf <name>\n"
		"add-to-shelf <bookName> <shelfName>\n"
		"remove-from-shelf <bookName> <shelfName>\n"
		"delete-book <bookName>\n"
		"show-shelf <reader>* <shelfName>\n"
		"show-inbox <filter>*\n"
		"read-msg <index>\n"
		"delete-msg <index>\n"
		"friends <reader>*\n"
		"add-birth <date>*\n"
		"profile <reader>*\n" 
		"accept-offer <index>\n"
		"leave <publisher>\n"
		"followers\n" << std::endl;
}

void Author::showInbox(const std::string& filter) const {
	if (inbox.size() == 0) {
		std::cout << "Your inbox is empty.\n";
		return;
	}
	if (filter == "") {
		std::cout << "Messages in your inbox:\n";
		for (size_t i = 0; i < inbox.size(); i++) {
			std::cout << i + 1 << ". from: " << inbox[i]->getMessenger() << ", status : " << (inbox[i]->getStatus() ? "read" : "unread") << "\n";
		}
	}
	else {
		int messageCount = 0;
		std::cout << "Job offers in your inbox:\n";
		for (size_t i = 0; i < inbox.size(); i++) {
			if (inbox[i]->getMessageContent().find(" has sent you a job offer") != std::string::npos) {
				std::cout << i + 1 << ". " << inbox[i]->getMessageContent() << " (from: " << inbox[i]->getMessenger() << ", status: " << (inbox[i]->getStatus() ? "read" : "unread") << ")\n";
				messageCount++;
			}
		}
		if (messageCount == 0) {
			std::cout << "You have no job offers yet.\n" << std::endl;
		}
	}
}
// WIP

std::string Author::getPublisher(const int index) {
	if (index < 1 || index > inbox.size()) {
		std::cout << "Invalid message index.\n" << std::endl;
		return "";
	}
	if (inbox[index - 1]->getMessageContent().find("has sent you a job offer") != std::string::npos) {
		std::string publisher = inbox[index - 1]->getMessenger();
		return publisher;
	}
	return "";
}

void Author::acceptOffer(const int index, const std::shared_ptr<User> publisher) {
	workWith(publisher);
	deleteMessage(index);
	std::cout << "You have accepted a job offer from " << publisher->getUsername() << ".\n" << std::endl;
}

void Author::workWith(const std::shared_ptr<User> user) {
	publishers.push_back(user);
}

void Author::leave(const std::shared_ptr<User> user) {
	for (size_t i = 0; i < publishers.size(); i++) {
		if (publishers[i].lock() == user) {
			publishers.erase(publishers.begin() + i);
			std::cout << "You have left " + user->getUsername() << ".\n" << std::endl;
			return;
		}
	}
	std::cout << "You cannot leave a publisher you are not working with.\n" << std::endl;
}

bool Author::hasSentJobOffer(std::shared_ptr<User> publisher) const {
	for (size_t i = 0; i < inbox.size(); i++) {
		if (inbox[i]->getMessenger() == publisher->getUsername()) {
			return true;
		}
	}
	return false;
}