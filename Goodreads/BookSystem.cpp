#include "BookSystem.h"

std::shared_ptr<Book> BookSystem::findBook(const std::string& bookName) const {
	for (auto book : books) {
		if (book->getTitle() == bookName) {
			return book;
		}
	}
	return nullptr;
}

void BookSystem::addBook(const std::shared_ptr<Book> book) {
	books.push_back(book);
}

std::vector<std::shared_ptr<Book>> BookSystem::getBooks() const {
	return books;
}

void BookSystem::loadBookSystem(std::fstream& file) {
	std::string booksCount;
	file >> booksCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(booksCount)); i++) {
		std::string title;
		file >> title;
		std::shared_ptr<Book> newBook = std::make_shared<Book>(title);
		newBook->loadBook(file);
		books.push_back(newBook);
	}
}

void BookSystem::saveBookSystem(std::fstream& file) const {
	file << std::to_string(books.size()) << '\n';
	for (auto book : books) {
		book->saveBook(file);
	}
}