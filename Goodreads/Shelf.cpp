#include <iostream>
#include "Shelf.h"

Shelf::Shelf(const std::string& name) {
	this->name = name;
}

std::string Shelf::getName() const {
	return name;
}

std::vector<std::weak_ptr<Book>>& Shelf::getBooks() {
	return books;
}

void Shelf::printShelf() const {
	for (const auto& weakBook : books) {
		if (auto book = weakBook.lock()) {
			std::cout << "- " << book->getTitle() << std::endl;
		}
	}
	if (books.size() == 0) {
		std::cout << "This shelf is empty.\n" << std::endl;
	}
}

void Shelf::addBook(std::shared_ptr<Book> book) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i].lock()->getTitle() == book->getTitle()) {
			std::cout << "Book is already on that shelf.\n" << std::endl;
			return;
		}
	}
	books.push_back(book);
	std::cout << "Book '" << book->getTitle() << "' added to shelf '" << getName() << "'\n" << std::endl;
}

void Shelf::removeBook(const std::string& bookName) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i].lock()->getTitle() == bookName) {
			books.erase(books.begin() + i);
			std::cout << "Book '" << bookName << "' removed from shelf '" << getName() << "'.\n" << std::endl;
			return;
		}
	}
	std::cout << "Book not found on that shelf.\n" << std::endl;
}