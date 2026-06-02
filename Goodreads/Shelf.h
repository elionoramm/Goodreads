#pragma once
#include "Book.h"
#include <string>
#include <vector>
#include <memory>
class Shelf {
private:
	std::string name;
	std::vector<Book> books;
public:
	Shelf(const std::string& name);
	std::string getName() const;
	void printShelf() const;
	bool addBook(const Book book);
	bool removeBook(const std::string& bookName);
	Book operator[] (size_t index) const;
	size_t size() const;
};