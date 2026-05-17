#pragma once
#include <vector>
#include <memory>
#include "Reader.h"
class Author : public Reader {
private:
	//std::vector<std::shared_ptr<Book>> booksPublished = {};
	//std::vector<std::weak_ptr<Publisher>> publishers = {};
	//std::vector<Message> inbox;
public:
	std::string getUserType() const override;
	Author(const std::string& username, const std::string& password);
};