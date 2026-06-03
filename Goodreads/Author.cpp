#include <iostream>
#include "Author.h"

Author::Author(const std::string& username, const std::string& password) : Reader(username, password) {}

void Author::loadUser(std::fstream& file) {
	Reader::loadUser(file);
	std::string booksPublishedCount;
	file >> booksPublishedCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(booksPublishedCount)); i++) {
		std::string title;
		file >> title;
		Book publishedBook = Book(title);
		publishedBook.loadBook(file);
		booksPublished.push_back(publishedBook);
	}
	std::string publishersCount;
	file >> publishersCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(publishersCount)); i++) {
		std::string publisher;
		file >> publisher;
		publishers.push_back(publisher);
	}
}

void Author::saveUser(std::fstream& file) const {
	Reader::saveUser(file);
	file << std::to_string(booksPublished.size()) << '\n';
	// saving the published books
	for (size_t i = 0; i < booksPublished.size(); i++) {
		booksPublished[i].saveBook(file);
	}
	file << std::to_string(publishers.size()) << '\n';
	// saving the publishers
	for (size_t i = 0; i < publishers.size(); i++) {
		file << publishers[i] << '\n';
	}
}

std::string Author::getUserType() const {
	return "author";
}

void Author::help() const {
	Reader::help();
	std::cout << "accept-offer <index>\n"
		"leave <publisher>\n"
		"followers\n";
}

void Author::showInbox(const std::string& filter) const {
	if (inbox.size() == 0) {
		std::cout << "Your inbox is empty.\n";
		return;
	}
	if (filter != "offers") {
		std::cout << "Messages in your inbox:\n";
		for (size_t i = 0; i < inbox.size(); i++) {
			std::cout << i + 1 << ". from: " << inbox[i].getMessenger() << ", status : " << (inbox[i].getStatus() ? "read" : "unread") << "\n";
		}
	}
	else {
		int messageCount = 0;
		std::cout << "Job offers in your inbox:\n";
		for (size_t i = 0; i < inbox.size(); i++) {
			if (inbox[i].getMessageContent().find(" has sent you a job offer") != std::string::npos) {
				std::cout << i + 1 << ". " << inbox[i].getMessageContent() << " (from: " << inbox[i].getMessenger() << ", status: " << (inbox[i].getStatus() ? "read" : "unread") << ")\n";
				messageCount++;
			}
		}
		if (messageCount == 0) {
			std::cout << "You have no job offers yet.\n" << std::endl;
		}
	}
}

std::string Author::getPublisher(const int index) {
	if (index < 1 || index > inbox.size()) {
		std::cout << "Invalid message index.\n" << std::endl;
		return "";
	}
	if (inbox[index - 1].getMessageContent().find("has sent you a job offer") != std::string::npos) {
		std::string publisher = inbox[index - 1].getMessenger();
		return publisher;
	}
	return "";
}

void Author::acceptOffer(const int index, const std::string publisher) {
	workWith(publisher);
	deleteMessage(index);
	std::cout << "You have accepted a job offer from " << publisher << ".\n" << std::endl;
}

void Author::workWith(const std::string& user) {
	publishers.push_back(user);
}

void Author::leave(const std::string& publisher) {
	for (size_t i = 0; i < publishers.size(); i++) {
		if (publishers[i] == publisher) {
			publishers.erase(publishers.begin() + i);
			std::cout << "You have left " + publisher << ".\n" << std::endl;
			return;
		}
	}
	std::cout << "You cannot leave a publisher you are not working with.\n" << std::endl;
}

void Author::publish(const std::shared_ptr<Book>& book) {
	booksPublished.push_back(*book);
}

bool Author::isWorkingWith(const std::string& user) const {
	for (size_t i = 0; i < publishers.size(); i++) {
		if (publishers[i] == user) {
			return true;
		}
	}
	return false;
}

bool Author::hasSentJobOffer(const std::string& publisher) const {
	for (size_t i = 0; i < inbox.size(); i++) {
		if (inbox[i].getMessenger() == publisher) {
			return true;
		}
	}
	return false;
}