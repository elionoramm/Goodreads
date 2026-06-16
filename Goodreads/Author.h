#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "Reader.h"
class Author : public Reader {
private:
	std::vector<std::shared_ptr<Book>> booksPublished;
	std::vector<std::string> publishers;
public:
	Author(const std::string& username, const std::string& password);
	void loadUser(std::fstream& file, const BookSystem& bookSystem) override;
	void saveUser(std::fstream& file) const override;
	std::string getUserType() const override;
	void help() const override;
	void showInbox(const std::string& filter) const override;
	void acceptOffer(const int index, const std::string publisher);
	std::string getPublisher(const int index);
	void addPublisher(const std::string& user);
	void leave(const std::string& publisher);
	void addToPublishedBooks(const std::shared_ptr<Book>& book);
	bool isWorkingWithPublisher(const std::string& publisher) const;
	bool hasAJobOfferFrom(const std::string& publisher) const;
};