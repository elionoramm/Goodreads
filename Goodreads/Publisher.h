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
	void loadUser(std::fstream& file) override;
	void saveUser(std::fstream& file) const override;
	std::string getUserType() const override;
	void help() const override;
	// for the reader commands
	void addBook(const std::shared_ptr<Book>& book, const std::string& status, const double rating) override;
	void createShelf(const std::string& shelfName) override;
	void deleteShelf(const std::string& shelfName) override;
	void addToShelf(const std::shared_ptr<Book>& book, const std::string& shelfName) override;
	void removeFromShelf(const std::string& bookName, const std::string& shelfName) override;
	void deleteBook(const std::string& bookName) override;
	void showShelf(const std::string& shelfName) const override;
	void showInbox(const std::string& filter) const override;
	void receiveMessage(const Message& message) override;
	void readMessage(const size_t& index) override;
	void deleteMessage(const size_t& index) override;
	void setBirthday(const Date& date) override;
	Date getBirthday() const override;
	void printShelves() const override;
	void printFavoriteBooks() const override;
	// for the author commands
	void acceptOffer(const int index, const std::string publisher) override;
	std::string getPublisher(const int index) override;
	void workWith(const std::string& user) override;
	void leave(const std::string& author) override;
	// for the publisher commands
	void publish(const std::shared_ptr<Book>& book) override;
	bool isWorkingWith(const std::string& user) const override;
	bool hasSentJobOffer(const std::string& publisher) const override;
	std::vector<std::shared_ptr<Book>> getBooks() const override;
	std::shared_ptr<Book> getBookByTitle(const std::string& title) const override;
};