#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Book.h"
#include "Shelf.h"
#include "Date.h"
#include "Message.h"

class Reader : public User {
protected:
	std::vector<std::tuple<Book, std::string, double>> profileBooks;
	std::vector<Shelf> shelves;
	std::vector<std::string> favoriteBooks;
	Date birthday;
	std::vector<Message> inbox;
public:
	Reader(const std::string& username, const std::string& password);
	void saveUser(std::fstream& file) const override;
	void loadUser(std::fstream& file) override;
	std::string getUserType() const override;
	void help() const override;
	// for the reader commands
	void addToCollection(const std::shared_ptr<Book>& book, const std::string& status, const double rating) override;
	void createShelf(const std::string& shelfName) override;
	void deleteShelf(const std::string& shelfName) override;
	void addToShelf(const std::shared_ptr<Book>& book, const std::string& shelfName) override;
	void removeFromShelf(const std::string& bookName, const std::string& shelfName) override;
	void deleteBook(const std::string& bookName) override;
	void showShelf(const std::string& shelfName) const override;
	void showInbox(const std::string& filter) const override;
	void receiveMessage(const Message& message) override;
	void readMessage(size_t index) override;
	void deleteMessage(size_t index) override;
	void setBirthday(const Date& date) override;
	Date getBirthday() const override;
	void printShelves() const override;
	void printFavoriteBooks() const override;
	// for the author commands
	void acceptOffer(const int index, const std::string publisher) override;
	std::string getPublisher(const int index) override;
	void workWith(const std::string user) override;
	void leave(std::string publisher) override;
	// for the publisher commands
	void publish(const std::shared_ptr<Book>& book) override;
	bool isWorkingWithAuthor(std::string author) const override;
	bool hasSentJobOffer(std::string publisher) const override;
	std::vector<std::shared_ptr<Book>> getBooks() const override;
	std::shared_ptr<Book> getBookByTitle(const std::string title) const override;
};