#include <iostream>
#include "Reader.h"
#include "Repository.cpp"
void Reader::accept(Visitor* visitor) const {
	visitor->visitReader(*this);
}

Reader::Reader(const std::string& username, const std::string& password) {
	this->username = username;
	this->password = password;
}

std::string Reader::getUserType() const {
	return "Reader";
}

void Reader::help() const {
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
		"add-birthday <date>*\n"
		"profile <reader>*\n" << std::endl;
}

// WIP what do we do about the status
void Reader::addToCollection(const std::shared_ptr<Book> book, const std::string& status, double rating) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i] == book) {
			std::cout << "Book already exists in your collection.\n" << std::endl;
			return;
		}
	}
	books.addElement(book);
	std::cout << "Book '" << book->getTitle() << "' added to your collection with status '" << status << "'\n" << std::endl;
	// Here you can also store the status of the book in the reader's collection
	if (rating != 0) {
		book->addReview(rating);
	}
}

void Reader::createShelf(const std::string& shelfName) {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			std::cout << "A shelf with this name already exists.\n" << std::endl;
			return;
		}
	}
	shelves.addElement(std::make_shared<Shelf>(shelfName));
	std::cout << "Shelf '" << shelfName << "' created successfully.\n" << std::endl;
}

void Reader::deleteShelf(const std::string& shelfName) {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			shelves.removeElement(i);
			std::cout << "Shelf '" << shelfName << "' deleted.\n" << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::addToShelf(const std::shared_ptr<Book> book, const std::string& shelfName) {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			shelves[i]->addBook(book);
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::removeFromShelf(const std::string& bookName, const std::string& shelfName) {
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			shelves[i]->removeBook(bookName);
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::deleteBook(const std::string& bookName) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i]->getTitle() == bookName) {
			books.removeElement(i);
			std::cout << "Book '" << bookName << "' removed from your collection.\n" << std::endl;
			return;
		}
	}
	std::cout << "Book not found in your collection.\n" << std::endl;
}

void Reader::showShelf(const std::string& shelfName) const {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			std::cout << "Books in shelf '" << shelfName << "':\n";
			shelves[i]->printShelf();
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::showInbox(const std::string& filter) const {
	if(inbox.size() == 0) {
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
		std::cout << "Friend requests in your inbox:\n";
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
	std::cout << message->getMessageContent() << "\n" << std::endl;
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

void Reader::printFriends() const {
	int friendCount = 0;
	std::cout << "Friends:\n";
	for (size_t i = 0; i < followers.size(); i++) {
		if (followers[i]->isFollowedBy(this->getUsername())) {
			std::cout << followers[i]->getUsername() << std::endl;
			friendCount++;
		}
	}
	if (friendCount == 0) {
		std::cout << "this user has no friends yet.\n" << std::endl;
	}
}

void Reader::setBirthday(const Date& date) {
	if (!birthday.isSet() && !date.isSet()) {
		std::cout << "Birthday erased successfully.\n" << std::endl;
		return;
	}
	if (birthday.isSet() && date.isSet()) {
		std::cout << "Birthday changed successfully.\n" << std::endl;
	}
	else if (date.isSet()) {
		std::cout << "Birthday added successfully.\n" << std::endl;
	}
	this->birthday = date;
}

Date Reader::getBirthday() const {
	return birthday;
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

void Reader::acceptOffer(const int index, const std::shared_ptr<User> publisher) {}

std::string Reader::getPublisher(const int index) {
	return "";
}

void Reader::workWith(const std::shared_ptr<User> author) {}

void Reader::leave(const std::shared_ptr<User> user) {}

void Reader::publish(std::shared_ptr<Book> book) {}

bool Reader::isWorkingWithAuthor(std::shared_ptr<User> author) const {
	return false;
}

bool Reader::hasSentJobOffer(std::shared_ptr<User> publisher) const {
	return false;
}