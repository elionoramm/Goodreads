#include <iostream>
#include "Publisher.h"

Publisher::Publisher(const std::string& username, const std::string& password) : User(username, password) {}

void Publisher::loadUser(std::fstream& file) {
	User::loadUser(file);
	std::string authorsCount;
	file >> authorsCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(authorsCount)); i++) {
		std::string authorName;
		file >> authorName;
		authors.push_back(authorName);
	}
	std::string booksPublishedCount;
	file >> booksPublishedCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(booksPublishedCount)); i++) {
		std::string bookTitle;
		file >> bookTitle;
		Book book = Book(bookTitle);
		book.loadBook(file);
		booksPublished.push_back(std::make_shared<Book>(book));
	}
}

void Publisher::saveUser(std::fstream& file) const {
	User::saveUser(file);
	file << std::to_string(authors.size()) << '\n';
	// saving the authors
	for (size_t i = 0; i < authors.size(); i++) {
		file << authors[i] << '\n';
	}
	// saving the published books
	file << std::to_string(booksPublished.size()) << '\n';
	for (size_t i = 0; i < booksPublished.size(); i++) {
		booksPublished[i]->saveBook(file);
	}
}

std::string Publisher::getUserType() const {
	return "publisher";
}

void Publisher::help() const {
	std::cout << "register <username> <password> <userType>\n"
		"login <username> <password>\n"
		"logout\n"
		"exit\n"
		"publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres>\n"
		"add-synopsis <bookTitle> <synopsis>\n"
		"offer <author>\n";
}

// for the reader commands
void Publisher::addToCollection(const std::shared_ptr<Book>& book, const std::string& status, const double rating) {
	std::cout << "Publishers cannot add books to their collection.\n" << std::endl;
}

void Publisher::createShelf(const std::string& shelfName) {
	std::cout << "Publishers cannot create shelves.\n" << std::endl;
}

void Publisher::deleteShelf(const std::string& shelfName) {
	std::cout << "Publishers cannot delete shelves.\n" << std::endl;
}

void Publisher::addToShelf(const std::shared_ptr<Book>& book, const std::string& shelfName) {
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

void Publisher::receiveMessage(const Message& message) {}

void Publisher::readMessage(size_t index) {}

void Publisher::deleteMessage(size_t index) {}

void Publisher::setBirthday(const Date& date) {}

Date Publisher::getBirthday() const {
	return Date();
}

void Publisher::printShelves() const {}

void Publisher::printFavoriteBooks() const {}

// for the author commands
void Publisher::acceptOffer(const int index, const std::string publisher) {}

std::string Publisher::getPublisher(const int index) {
	return "";
}

void Publisher::workWith(const std::string user) {
	authors.push_back(user);
}

void Publisher::leave(const std::string author) {
	for (size_t i = 0; i < authors.size(); i++) {
		if (authors[i] == author) {
			authors.erase(authors.begin() + i);
			return;
		}
	}
}
// for the publisher commands
void Publisher::publish(const std::shared_ptr<Book>& book) {
	booksPublished.push_back(book);
}

bool Publisher::isWorkingWithAuthor(std::string author) const {
	for (size_t i = 0; i < authors.size(); i++) {
		if (authors[i] == author) {
			return true;
		}
	}
	return false;
}

bool Publisher::hasSentJobOffer(std::string publisher) const {
	return false;
}

std::vector<std::shared_ptr<Book>> Publisher::getBooks() const {
	return booksPublished;
}

std::shared_ptr<Book> Publisher::getBookByTitle(const std::string title) const {
	for (size_t i = 0; i < booksPublished.size(); i++) {
		if (booksPublished[i]->getTitle() == title) {
			return booksPublished[i];
		}
	}
	return nullptr;
}