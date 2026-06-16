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
	std::vector<std::tuple<std::shared_ptr<Book>, std::string, double>> profileBooks;
	std::vector<Shelf> shelves;
	std::vector<std::shared_ptr<Book>> favoriteBooks;
	Date birthday;
	std::vector<Message> inbox;
public:
	Reader(const std::string& username, const std::string& password);
	void saveUser(std::fstream& file) const override;
	void loadUser(std::fstream& file, const BookSystem& bookSystem) override;
	std::string getUserType() const override;
	void help() const override;
	void addBook(const std::shared_ptr<Book>& book, const std::string& status, const double rating);
	void createShelf(const std::string& shelfName);
	void deleteShelf(const std::string& shelfName);
	void addToShelf(const std::shared_ptr<Book>& book, const std::string& shelfName);
	void removeFromShelf(const std::string& bookName, const std::string& shelfName);
	void deleteBook(const std::string& bookName);
	void showShelf(const std::string& shelfName) const;
	virtual void showInbox(const std::string& filter) const;
	void receiveMessage(const Message& message);
	void readMessage(const size_t& index);
	void deleteMessage(const size_t& index);
	void setBirthday(const Date& date);
	Date getBirthday() const;
	void printShelves() const;
	void printFavoriteBooks() const;
};