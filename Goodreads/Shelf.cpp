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
}