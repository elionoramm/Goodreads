#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "UserFactory.h"
#include "User.h"
#include "UserSystem.h"
#include "UsernameValidator.h"
#include "PasswordValidator.h"
#include "CustomUserExceptions.h"
#include "Book.h"

class GoodReads {
private:
	UserSystem userSystem;
	std::shared_ptr<User> activeUser;
public:
	GoodReads();
	std::shared_ptr<User> findUser(const std::string& username) const;
	std::shared_ptr<Book> findBook(const std::string& bookName) const;
	std::shared_ptr<User> getActiveUser() const;
	void help(const std::vector<std::string>& params) const;
	void registerUser(const std::vector<std::string>& params);
	void logIn(const std::vector<std::string>& params);
	void logOut(const std::vector<std::string>& params);
	void exit(const std::vector<std::string>& params);
	// for the reader commands
	bool caseInsensitiveMatch(const std::string& str1, const std::string& str2) const; // helper function
	void search(const std::vector<std::string>& params) const;
	void follow(const std::vector<std::string>& params);
	void addBook(const std::vector<std::string>& params);
	void createShelf(const std::vector<std::string>& params);
	void deleteShelf(const std::vector<std::string>& params);
	void addToShelf(const std::vector<std::string>& params);
	void removeFromShelf(const std::vector<std::string>& params);
	void deleteBook(const std::vector<std::string>& params);
	void showShelf(const std::vector<std::string>& params) const;
	void showInbox(const std::vector<std::string>& params) const;
	void readMessage(const std::vector<std::string>& params);
	void deleteMessage(const std::vector<std::string>& params);
	void friends(const std::vector<std::string>& params) const;
	void addBirthday(const std::vector<std::string>& params);
	void profile(const std::vector<std::string>& params) const;
	// for the author commands
	void acceptOffer(const std::vector<std::string>& params) const;
	void leave(const std::vector<std::string>& params);
	void followers(const std::vector<std::string>& params) const;
	// for the publisher commands
	void publish(const std::vector<std::string>& params);
	void addSynopsis(const std::vector<std::string>& params);
	void offer(const std::vector<std::string>& params);
};