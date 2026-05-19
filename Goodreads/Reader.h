#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Repository.h"
#include "Book.h"
#include "Shelf.h"
#include "Date.h"
#include "Message.h"

class Reader : public User {
protected:
	Repository<Book> books;
	Repository<Shelf> shelves;
	std::vector<std::weak_ptr<Book>> favoriteBooks;
	Date birthday;
	Repository<User> followers; // should be weak_ptr?
	Repository<Message> inbox;
public:
	Reader(const std::string& username, const std::string& password);
	Reader(std::shared_ptr<User> user);
	std::string getUserType() const override;
	Repository<Book>& getBooks();
	Repository<Shelf>& getShelves();
	std::vector<std::weak_ptr<Book>>& getShelfBooks(const std::string& shelfName) const;
	Date getBirthday() const;
	Repository<User>& getFollowers();
	void setBirthday(const Date& date);
	void addBook(const std::shared_ptr<Book> book, const std::string& status, double rating);
	void createShelf(const std::string& shelfName);
	void showInbox(const std::string& filter) const;
	void receiveMessage(const std::shared_ptr<Message> message);
	void readMessage(size_t index);
	void deleteMessage(size_t index);
	void printShelves() const;
	void printFavoriteBooks() const;
	void printFriends(const std::shared_ptr<Reader> reader) const;
};