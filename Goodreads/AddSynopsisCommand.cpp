#include "AddSynopsisCommand.h"

AddSynopsis::AddSynopsis(GoodReads& goodReads) : goodReads(goodReads) {}

void AddSynopsis::execute(std::vector<std::string> params) {
	std::shared_ptr<Publisher> activeUser = goodReads.getActivePublisher();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() < 2) {
		throw WrongCommandUsage("Usage: add-synopsis <bookTitle> <synopsis>\n");
	}
	std::string bookName = params[0];
	std::string synopsis = "";
	for (size_t i = 1; i < params.size(); i++) {
		synopsis = synopsis + params[i] + " ";
	}
	std::shared_ptr<Book> book = activeUser->getBookByTitle(bookName);
	if (book == nullptr) {
		throw std::invalid_argument("You cannot add a synopsis to a book that wasn't published by you.\n");
	}
	else if (book->getSynopsis() != "") {
		throw std::logic_error("This book already has a synopsis.\n");
	}
	book->addSynopsis(synopsis);
	std::cout << "You have successfully added a synopsis to " << bookName << ".\n" << std::endl;
}