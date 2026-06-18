#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "Book.h"
#include "BookSystem.h"
#include "User.h"
#include "Reader.h"
#include "Author.h"
#include "Publisher.h"
#include "UserSystem.h"
#include "UsernameValidator.h"
#include "PasswordValidator.h"
#include "CustomUserExceptions.h"


class GoodReads {
private:
	BookSystem bookSystem;
	UserSystem userSystem;
	std::shared_ptr<User> activeUser;
public:
	GoodReads();
	UserSystem& getUserSystem();
	BookSystem& getBookSystem();
	std::shared_ptr<User> findUser(const std::string& username) const;
	std::shared_ptr<Book> findBook(const std::string& bookName) const;
	std::shared_ptr<User> getActiveUser() const;
	std::shared_ptr<Reader> getActiveReader() const;
	std::shared_ptr<Author> getActiveAuthor() const;
	std::shared_ptr<Publisher> getActivePublisher() const;
	std::shared_ptr<Reader> toReader(const std::shared_ptr<User> user) const;
	std::shared_ptr<Author> toAuthor(const std::shared_ptr<User> user) const;
	std::shared_ptr<Publisher> toPublisher(const std::shared_ptr<User> user) const;
	void setActiveUser(std::shared_ptr<User> user);
};