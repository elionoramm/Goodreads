#pragma once
#include "Book.h"
#include <string>
#include <vector>
#include <memory>
class Shelf {
private:
	std::string name;
	std::vector<std::shared_ptr<Book>> books;
public:
	Shelf(const std::string& name);
	std::string getName() const;
	void printShelf() const;
	bool addBook(const std::shared_ptr<Book> book);
	bool removeBook(const std::string& bookName);
	std::shared_ptr <Book> operator[] (size_t index) const;
	size_t size() const;
};