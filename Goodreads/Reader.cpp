#include <iostream>
#include "Reader.h"
#include "Repository.cpp"

Reader::Reader(const std::string& username, const std::string& password) {
	this->username = username;
	this->password = password;
}

Reader::Reader(std::shared_ptr<User> user) {
	this->username = user->getUsername();
	this->password = user->getPassword();
}

std::string Reader::getUserType() const {
	return "Reader";
}

Repository<Book>& Reader::getBooks() {
	return books;
}

Repository<Shelf>& Reader::getShelves() {
	return shelves;
}

std::vector<std::weak_ptr<Book>>& Reader::getShelfBooks(const std::string& shelfName) const {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			return shelves[i]->getBooks();
		}
	}
	throw std::runtime_error("Shelf not found.");
}

Date Reader::getBirthday() const {
	return birthday;
}

Repository<User>& Reader::getFollowers() {
	return followers;
}

void Reader::setBirthday(const Date& date) {
	this->birthday = date;
}
// WIP what do we do about the status
void Reader::addBook(const std::shared_ptr<Book> book, const std::string& status, double rating) {
	books.addElement(book);
	// Here you can also store the status of the book in the reader's collection
	if (rating != 0) {
		book->addReview(rating);
	}
}

void Reader::createShelf(const std::string& shelfName) {
	shelves.addElement(std::make_shared<Shelf>(shelfName));
}

void Reader::showInbox(const std::string& filter) const {
	if(inbox.size() == 0) {
		std::cout << "Your inbox is empty.\n" << std::endl;
		return;
	}
	if (filter == "") {
		for (size_t i = 0; i < inbox.size(); i++) {
			std::cout << i + 1 << ". " << inbox[i]->getMessageContent() << " (from: " << inbox[i]->getMessenger() << ", status: " << (inbox[i]->getStatus() ? "read" : "unread") << ")\n";
		}
	}
	else {
		for (size_t i = 0; i < inbox.size(); i++) {
			if (inbox[i]->getMessageContent().find("has sent you a friend request") != std::string::npos) {
				std::cout << i + 1 << ". " << inbox[i]->getMessageContent() << " (from: " << inbox[i]->getMessenger() << ", status: " << (inbox[i]->getStatus() ? "read" : "unread") << ")\n";
			}
		}
	}
}

void Reader::receiveMessage(const std::shared_ptr<Message> message) {
	inbox.addElement(message);
}

void Reader::readMessage(size_t index) {
	if (index < 1 || index > inbox.size()) {
		std::cout << "Invalid message index.\n" << std::endl;
		return;
	}
	std::shared_ptr<Message> message = inbox[index - 1];
	std::cout << "Message from " << message->getMessenger() << ": " << message->getMessageContent() << "\n";
	message->markAsRead();
}

void Reader::deleteMessage(size_t index) {
	if (index < 1 || index > inbox.size()) {
		std::cout << "Invalid message index.\n" << std::endl;
		return;
	}
	inbox.removeElement(index - 1);
	std::cout << "Message deleted.\n" << std::endl;
}

void Reader::printShelves() const {
	if (shelves.size() == 0) {
		std::cout << "No shelves in this profile." << std::endl;
		return;
	}
	for (size_t i = 0; i < shelves.size(); i++) {
		std::cout << "- " << shelves[i]->getName() << "\n";
	}
	std::cout << std::endl;
}

void Reader::printFavoriteBooks() const {
	if (favoriteBooks.size() == 0) {
		std::cout << "No favorite books in this profile." << std::endl;
		return;
	}
	std::cout << "Your favorite books:\n";
	for (size_t i = 0; i < favoriteBooks.size(); i++) {
		if (auto book = favoriteBooks[i].lock()) {
			std::cout << "- " << book->getTitle() << "\n";
		}
	}
	std::cout << std::endl;
}

void Reader::printFriends(const std::shared_ptr<Reader> reader) const {
	int friendCount = 0;
	for (size_t i = 0; i < reader->getFollowers().size(); i++) {
		std::shared_ptr<Reader> friendReader = std::dynamic_pointer_cast<Reader>(reader->getFollowers()[i]);
		for (size_t j = 0; j < friendReader->getFollowers().size(); j++) {
			if (friendReader->getFollowers()[j] == reader) {
				std::cout << friendReader->getUsername() << " (" << friendReader->getUserType() << ")\n";
				friendCount++;
			}
		}
	}
	if (friendCount == 0) {
		std::cout << "You have no friends yet.\n" << std::endl;
	}
}