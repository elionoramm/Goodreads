#include "RemoveFromShelfCommand.h"

RemoveFromShelf::RemoveFromShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void RemoveFromShelf::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 2) {
		throw WrongCommandUsage("Usage: remove-from-shelf <bookName> <shelfName>\n");
	}
	std::string bookName = params[0];
	std::string shelfName = params[1];
	activeUser->removeFromShelf(bookName, shelfName);
}