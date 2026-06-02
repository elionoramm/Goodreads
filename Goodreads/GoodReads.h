#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "UserFactory.h"
#include "User.h"
#include "Reader.h"
#include "Author.h"
#include "Publisher.h"
#include "Book.h"

class GoodReads {
private:
	std::vector<std::shared_ptr<User>> users;
	std::shared_ptr<User> activeUser;
public:
	GoodReads();
	void help(const std::vector<std::string>& params) const;
	void registerUser(const std::vector<std::string>& params);
	void logIn(const std::vector<std::string>& params);
	void logOut(const std::vector<std::string>& params);
	void exit(const std::vector<std::string>& params);
	// for the reader commands
	bool caseInsensitiveMatch(const std::string& str1, const std::string& str2) const; // helper function
	void search(const std::vector<std::string>& params) const;
	void follow(const std::vector<std::string>& params);
	void addToCollection(const std::vector<std::string>& params);
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