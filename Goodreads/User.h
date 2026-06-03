#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <time.h>
#include "Date.h"
#include "Book.h"
#include "Message.h"
#include "CustomUserExceptions.h"

class User {
protected:
	std::string username;
	std::string password;
	Date registrationDate;
	std::vector<std::string> followers;
public:
	User(const std::string& username, const std::string& password);
	virtual ~User() = default;
	virtual void loadUser(std::fstream& file);
	virtual void saveUser(std::fstream& file) const;
	virtual std::string getUserType() const = 0;
	std::string getUsername() const;
	std::string getPassword() const;
	Date getRegistrationDate() const;
	std::vector<std::string> getFollowers() const;
	void printFollowers() const;
	virtual void help() const = 0;
	// for the reader commands
	void addFollower(const std::string follower);
	virtual void addBook(const std::shared_ptr<Book>& book, const std::string& status, const double rating) = 0;
	virtual void createShelf(const std::string& shelfName) = 0;
	virtual void deleteShelf(const std::string& shelfName) = 0;
	virtual void addToShelf(const std::shared_ptr<Book>& book, const std::string& shelfName) = 0;
	virtual void removeFromShelf(const std::string& bookName, const std::string& shelfName) = 0;
	virtual void deleteBook(const std::string& bookName) = 0;
	virtual void showShelf(const std::string& shelfName) const = 0;
	virtual void printShelves() const = 0;
	virtual void showInbox(const std::string& filter) const = 0;
	virtual void receiveMessage(const Message& message) = 0;
	virtual void readMessage(const size_t& index) = 0;
	virtual void deleteMessage(const size_t& index) = 0;
	bool isFollowedBy(const std::string& username) const;
	virtual void setBirthday(const Date& date) = 0;
	virtual Date getBirthday() const = 0;
	virtual void printFavoriteBooks() const = 0;
	// for the author commands
	virtual void acceptOffer(const int index, const std::string publisher) = 0;
	virtual std::string getPublisher(const int index) = 0;
	virtual void workWith(const std::string& user) = 0;
	virtual void leave(const std::string& publisher) = 0;
	// for the publisher commands
	virtual void publish(const std::shared_ptr<Book>& book) = 0;
	virtual bool isWorkingWith(const std::string& user) const = 0;
	virtual bool hasSentJobOffer(const std::string& publisher) const = 0;
	virtual std::vector<std::shared_ptr<Book>> getBooks() const = 0;
	virtual std::shared_ptr<Book> getBookByTitle(const std::string& title) const = 0;
	friend class PasswordValidator;
	friend class UsernameValidator;
};