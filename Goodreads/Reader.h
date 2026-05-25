#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Repository.h"
#include "Book.h"
#include "Shelf.h"
#include "Date.h"
#include "Message.h"
//#include "Visitor.h"

class Reader : public User {
protected:
	Repository<Book> books;
	Repository<Shelf> shelves;
	std::vector<std::weak_ptr<Book>> favoriteBooks;
	Date birthday;
	Repository<Message> inbox;
public:
	void accept(Visitor* visitor) const override;
	Reader(const std::string& username, const std::string& password);
	std::string getUserType() const override;
	void help() const override;
	// for the reader commands
	void addToCollection(const std::shared_ptr<Book> book, const std::string& status, double rating) override;
	void createShelf(const std::string& shelfName) override;
	void deleteShelf(const std::string& shelfName) override;
	void addToShelf(const std::shared_ptr<Book> book, const std::string& shelfName) override;
	void removeFromShelf(const std::string& bookName, const std::string& shelfName) override;
	void deleteBook(const std::string& bookName) override;
	void showShelf(const std::string& shelfName) const override;
	void showInbox(const std::string& filter) const override;
	void receiveMessage(const std::shared_ptr<Message> message) override;
	void readMessage(size_t index) override;
	void deleteMessage(size_t index) override;
	void printFriends() const override;
	void setBirthday(const Date& date) override;
	Date getBirthday() const override;
	void printShelves() const override;
	void printFavoriteBooks() const override;
	// for the author commands
	void acceptOffer(const int index, const std::shared_ptr<User> publisher) override;
	std::string getPublisher(const int index) override;
	void workWith(const std::shared_ptr<User> author) override;
	void leave(std::shared_ptr<User> user) override;
	// for the publisher commands
	void publish(std::shared_ptr<Book> book) override;
	bool isWorkingWithAuthor(std::shared_ptr<User> author) const override;
	bool hasSentJobOffer(std::shared_ptr<User> publisher) const override;
};