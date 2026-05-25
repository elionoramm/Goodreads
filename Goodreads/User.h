#pragma once
#include <string>
#include <memory>
#include "Date.h"
#include "Book.h"
#include "Message.h"
#include "Repository.h"
#include "Visitor.h"

class User {
protected:
	std::string username;
	std::string password;
	Date registrationDate;
	Repository<User> followers;
public:
	virtual void accept(Visitor* visitor) const = 0;
	virtual std::string getUserType() const = 0;
	std::string getUsername() const;
	std::string getPassword() const;
	Date getRegistrationDate() const;
	void printFollowers() const;
	virtual void help() const = 0;
	// for the reader commands
	void addFollower(const std::shared_ptr<User> follower);
	virtual void addToCollection(const std::shared_ptr<Book> book, const std::string& status, double rating) = 0;
	virtual void createShelf(const std::string& shelfName) = 0;
	virtual void deleteShelf(const std::string& shelfName) = 0;
	virtual void addToShelf(const std::shared_ptr<Book> book, const std::string& shelfName) = 0;
	virtual void removeFromShelf(const std::string& bookName, const std::string& shelfName) = 0;
	virtual void deleteBook(const std::string& bookName) = 0;
	virtual void showShelf(const std::string& shelfName) const = 0;
	virtual void printShelves() const = 0;
	virtual void showInbox(const std::string& filter) const = 0;
	virtual void receiveMessage(const std::shared_ptr<Message> message) = 0;
	virtual void readMessage(size_t index) = 0;
	virtual void deleteMessage(size_t index) = 0;
	virtual void printFriends() const = 0;
	bool isFollowedBy(const std::string& username) const;
	virtual void setBirthday(const Date& date) = 0;
	virtual Date getBirthday() const = 0;
	virtual void printFavoriteBooks() const = 0;
	// for the author commands
	virtual void acceptOffer(const int index, const std::shared_ptr<User> publisher) = 0;
	virtual std::string getPublisher(const int index) = 0;
	virtual void workWith(const std::shared_ptr<User> author) = 0;
	virtual void leave(const std::shared_ptr<User> user) = 0;
	// for the publisher commands
	virtual void publish(std::shared_ptr<Book> book) = 0;
	virtual bool isWorkingWithAuthor(std::shared_ptr<User> author) const = 0;
	virtual bool hasSentJobOffer(std::shared_ptr<User> publisher) const = 0;
};