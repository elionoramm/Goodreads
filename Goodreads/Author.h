#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "Reader.h"
class Author : public Reader {
private:
	std::vector<Book> booksPublished;
	std::vector<std::string> publishers;
public:
	Author(const std::string& username, const std::string& password);
	void loadUser(std::fstream& file) override;
	void saveUser(std::fstream& file) const override;
	std::string getUserType() const override;
	void help() const override;
	// for the author commands
	void showInbox(const std::string& filter) const override;
	void acceptOffer(const int index, const std::string publisher) override;
	std::string getPublisher(const int index) override;
	void workWith(const std::string& user) override;
	void leave(const std::string& publisher) override;
	// for the publisher commands
	void publish(const std::shared_ptr<Book>& book) override;
	bool isWorkingWith(const std::string& user) const override;
	bool hasSentJobOffer(const std::string& publisher) const override;
};