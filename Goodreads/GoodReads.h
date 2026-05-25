#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "User.h"
#include "Reader.h"
#include "Author.h"
#include "Publisher.h"
#include "Book.h"
//#include "Visitor.h";

class GoodReads {
private:
	std::vector<std::shared_ptr<User>> users;
	std::shared_ptr<User> activeUser;
	std::vector<std::shared_ptr<Book>> books;
public:
	void help() const;
	void registerUser(const std::string& username, const std::string& password, const std::string& role);
	void logIn(const std::string& username, const std::string& password);
	void logOut();
	void exit();
	// for the reader commands
	bool caseInsensitiveMatch(const std::string& str1, const std::string& str2) const;
	void search(const std::string& name) const;
	void follow(const std::string& username);
	void addToCollection(const std::string& bookName, const std::string& status, double rating);
	void createShelf(const std::string& shelfName);
	void deleteShelf(const std::string& shelfName);
	void addToShelf(const std::string& bookName, const std::string& shelfName);
	void removeFromShelf(const std::string& bookName, const std::string& shalfName);
	void deleteBook(const std::string& bookName);
	void showShelf(const std::string& username, const std::string& shelfName) const;
	void showInbox(const std::string& filter) const;
	void readMessage(const int index);
	void deleteMessage(const int index);
	void friends(const std::string& username) const;
	void addBirthday(const Date& birthday);
	void profile(const std::string& username) const;
	// for the author commands
	void acceptOffer(const int index) const;
	void leave(const std::string publisherName);
	void followers() const;
	// for the publisher commands
	void publish(const std::string title, const std::string authorName, const Date releaseDate, const int pageCount, const std::vector<std::string> genres);
	void addSynopsis(const std::string bookTitle, const std::string synopsis);
	void offer(const std::string authorName);
	// just for testing
	void addBook(const std::shared_ptr<Book> book);
};