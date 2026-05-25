#include <iostream>
#include "Publisher.h"
//visitor
void Publisher::accept(Visitor* visitor) const {
	visitor->visitPublisher(*this);
}

Publisher::Publisher(const std::string& username, const std::string& password) {
	this->username = username;
	this->password = password;
}

std::string Publisher::getUserType() const {
	return "Publisher";
}

void Publisher::help() const {
	std::cout << "register <username> <password> <userType>\n"
		"login <username> <password>\n"
		"logout\n"
		"exit\n"
		"publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres>\n"
		"add-synopsis <bookTitle> <synopsis>\n"
		"offer <author>\n" << std::endl;
}

// for the reader commands

void Publisher::addToCollection(const std::shared_ptr<Book> book, const std::string& status, double rating) {
	std::cout << "Publishers cannot add books to their collection.\n" << std::endl;
}

void Publisher::createShelf(const std::string& shelfName) {
	std::cout << "Publishers cannot create shelves.\n" << std::endl;
}

void Publisher::deleteShelf(const std::string& shelfName) {
	std::cout << "Publishers cannot delete shelves.\n" << std::endl;
}

void Publisher::addToShelf(const std::shared_ptr<Book> book, const std::string& shelfName) {
	std::cout << "Publishers cannot add books to shelves.\n" << std::endl;
}

void Publisher::removeFromShelf(const std::string& bookName, const std::string& shelfName) {
	std::cout << "Publishers cannot remove books from shelves.\n" << std::endl;
}

void Publisher::deleteBook(const std::string& bookName) {
	std::cout << "Publishers cannot delete books form their collection.\n" << std::endl;
}

void Publisher::showShelf(const std::string& shelfName) const {
	std::cout << "Publishers cannot have shelves.\n" << std::ends;
}

void Publisher::showInbox(const std::string& filter) const {}
void Publisher::receiveMessage(const std::shared_ptr<Message> message) {}
void Publisher::readMessage(size_t index) {}
void Publisher::deleteMessage(size_t index) {}
void Publisher::printFriends() const {}
void Publisher::setBirthday(const Date& date) {}
Date Publisher::getBirthday() const {
	return Date();
}
void Publisher::printShelves() const {}
void Publisher::printFavoriteBooks() const {}

// for the author commands
void Publisher::acceptOffer(const int index, const std::shared_ptr<User> publisher) {}

std::string Publisher::getPublisher(const int index) {
	return "";
}

void Publisher::workWith(const std::shared_ptr<User> author) {
	authors.push_back(author);
}

void Publisher::leave(const std::shared_ptr<User> user) {
	for (size_t i = 0; i < authors.size(); i++) {
		if (authors[i].lock() == user) {
			authors.erase(authors.begin() + i);
			return;
		}
	}
}
// for the publisher commands
void Publisher::publish(std::shared_ptr<Book> book) {
	booksPublished.push_back(book);
}

bool Publisher::isWorkingWithAuthor(std::shared_ptr<User> author) const {
	for (size_t i = 0; i < authors.size(); i++) {
		if (authors[i].lock() == author) {
			return true;
		}
	}
	return false;
}

bool Publisher::hasSentJobOffer(std::shared_ptr<User> publisher) const {
	return false;
}