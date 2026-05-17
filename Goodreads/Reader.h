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
	//std::vector <std::shared_ptr<Book>> books;
	//std::vector <Shelf> shelves;
	//std::vector <std::weak_ptr<Book>> favoriteBooks;
	//Date birthday; // optional for the reader
	//std::vector<Message> inbox;
public:
	std::string getUserType() const override;
	Reader(const std::string& username, const std::string& password);
};