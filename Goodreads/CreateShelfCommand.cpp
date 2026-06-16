#include "CreateShelfCommand.h"

CreateShelf::CreateShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void CreateShelf::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: create-shelf <name>\n");
	}
	std::string shelfName = params[0];
	activeUser->createShelf(shelfName);
}