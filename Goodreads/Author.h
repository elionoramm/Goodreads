#pragma once
#include <vector>
#include <memory>
#include "Reader.h"
//#include "Visitor.h"
class Author : public Reader {
private:
	//std::vector<std::shared_ptr<Book>> booksPublished;
	std::vector<std::weak_ptr<User>> publishers;
public:
	void accept(Visitor* visitor) const override;
	Author(const std::string& username, const std::string& password);
	std::string getUserType() const override;
	void help() const override;
	void showInbox(const std::string& filter) const override;
	void acceptOffer(const int index, const std::shared_ptr<User> publisher) override;
	std::string getPublisher(const int index) override;
	void workWith(const std::shared_ptr<User> author) override;
	void leave(const std::shared_ptr<User> user) override;
	bool hasSentJobOffer(std::shared_ptr<User> publisher) const override;
};