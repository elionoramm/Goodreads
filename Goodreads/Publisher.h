#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Author.h"
#include "Book.h"

class Publisher : public User {
private:
	//std::vector<std::weak_ptr<Author>> authors;
	//std::vector<std::shared_ptr<Book>> booksPublished;
public:
	std::string getUserType() const override;
	Publisher(const std::string& username, const std::string& password);
};