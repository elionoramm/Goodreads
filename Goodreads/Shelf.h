#pragma once
#include "Book.h"
#include <string>
#include <vector>
#include <memory>
class Shelf {
private:
	std::string name;
	std::vector<std::weak_ptr<Book>> books;
public:
	Shelf(const std::string& name);
	std::string getName() const;
	std::vector<std::weak_ptr<Book>>& getBooks();
	void printShelf() const;
};