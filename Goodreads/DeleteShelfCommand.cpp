#include "DeleteShelfCommand.h"

DeleteShelf::DeleteShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteShelf::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: delete-shelf <name>\n");
	}
	std::string shelfName = params[0];
	activeUser->deleteShelf(shelfName);
}