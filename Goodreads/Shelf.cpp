#include <iostream>
#include "Shelf.h"

Shelf::Shelf(const std::string& name) {
	this->name = name;
}

std::string Shelf::getName() const {
	return name;
}

void Shelf::printShelf() const {
	for (size_t i = 0; i < books.size(); i++) {
		std::cout << "- " << books[i].getTitle() << std::endl;
	}
	if (books.size() == 0) {
		std::cout << "This shelf is empty.\n" << std::endl;
	}
}

bool Shelf::addBook(const Book book) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i].getTitle() == book.getTitle()) {
			return false;
		}
	}
	books.push_back(book);
	return true;
}

bool Shelf::removeBook(const std::string& bookName) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i].getTitle() == bookName) {
			books.erase(books.begin() + i);
			std::cout << "Book '" << bookName << "' removed from shelf '" << getName() << "'.\n" << std::endl;
			return true;
		}
	}
	return false;
}

Book Shelf::operator[] (size_t index) const {
	return books[index];
}

size_t Shelf::size() const {
	return books.size();
}