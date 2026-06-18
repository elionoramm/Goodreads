#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "User.h"
#include "Reader.h"
#include "Author.h"
#include "Book.h"

class Publisher : public User {
private:
	std::vector<std::string> authors;
	std::vector<std::shared_ptr<Book>> booksPublished;
public:
	Publisher(const std::string& username, const std::string& password);
	void loadUser(std::fstream& file, const BookSystem& bookSystem) override;
	void saveUser(std::fstream& file) const override;
	std::string getUserType() const override;
	void help() const override;
	void addAuthor(const std::string& user);
	void addToPublishedBooks(const std::shared_ptr<Book>& book);
	bool isWorkingWithAuthor(const std::string& author) const;
	void removeAuthor(const std::string& author);
	std::shared_ptr<Book> getBookByTitle(const std::string& title) const;
};