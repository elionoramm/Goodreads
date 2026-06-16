#include <iostream>
#include "Publisher.h"

Publisher::Publisher(const std::string& username, const std::string& password) : User(username, password) {}

void Publisher::loadUser(std::fstream& file, const BookSystem& bookSystem) {
	User::loadUser(file, bookSystem);
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
		booksPublished.push_back(bookSystem.findBook(bookTitle));
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
		file << booksPublished[i]->getTitle() << '\n';
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

void Publisher::addAuthor(const std::string& user) {
	authors.push_back(user);
}

void Publisher::addToPublishedBooks(const std::shared_ptr<Book>& book) {
	booksPublished.push_back(book);
}

bool Publisher::isWorkingWithAuthor(const std::string& author) const {
	for (size_t i = 0; i < authors.size(); i++) {
		if (authors[i] == author) {
			return true;
		}
	}
	return false;
}

bool Publisher::hasSentJobOffer(const std::string& publisher) const {
	return false;
}

std::vector<std::shared_ptr<Book>> Publisher::getBooks() const {
	return booksPublished;
}

std::shared_ptr<Book> Publisher::getBookByTitle(const std::string& title) const {
	for (size_t i = 0; i < booksPublished.size(); i++) {
		if (booksPublished[i]->getTitle() == title) {
			return booksPublished[i];
		}
	}
	return nullptr;
}