#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "Book.h"

class BookSystem {
private:
	std::vector<std::shared_ptr<Book>> books;
public:
	BookSystem() = default;
	std::shared_ptr<Book> findBook(const std::string& bookName) const;
	void addBook(const std::shared_ptr<Book> book);
	std::vector<std::shared_ptr<Book>> getBooks() const;
	void loadBookSystem(std::fstream& file);
	void saveBookSystem(std::fstream& file) const;
};