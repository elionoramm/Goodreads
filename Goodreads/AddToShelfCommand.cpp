#include "AddToShelfCommand.h"

AddToShelf::AddToShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void AddToShelf::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 2) {
		throw WrongCommandUsage("Usage: add-to-shelf <bookName> <shelfName>\n");
	}
	std::string bookName = params[0];
	std::string shelfName = params[1];
	std::shared_ptr<Book> book = goodReads.findBook(bookName);
	if (book == nullptr) {
		throw std::invalid_argument("Book not found in the system.\n");
	}
	activeUser->addToShelf(book, shelfName);
}