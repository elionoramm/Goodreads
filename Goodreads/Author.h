#pragma once
#include <vector>
#include <memory>
#include "Reader.h"
class Author : public Reader {
private:
	//std::vector<std::shared_ptr<Book>> booksPublished;
	//std::vector<std::weak_ptr<Publisher>> publishers;
public:
	Author(const std::string& username, const std::string& password);
	std::string getUserType() const override;
};