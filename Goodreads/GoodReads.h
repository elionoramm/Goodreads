#pragma once
#include <memory>
#include <vector>
#include <string>
#include "User.h"
#include "Book.h"
#include "Reader.h"
#include "Author.h"
#include "Publisher.h"
#include "Repository.h"
#include "Command.h"
#include "Commands.h"

class GoodReads {
	Repository<User> users;
	Repository<Book> books;
	std::shared_ptr<User> activeUser;
public:
	static std::unique_ptr<GoodReads> instance;
	void setActiveUser(std::shared_ptr<User> user);
	std::shared_ptr<User> getActiveUser() const;
	Repository<User>& getUsers();
	Repository<Book>& getBooks();
	void ExecuteCommand(const std::string& line);
};