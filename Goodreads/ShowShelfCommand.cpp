#include "ShowShelfCommand.h"

ShowShelf::ShowShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowShelf::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1 && params.size() != 2) {
		throw WrongCommandUsage("Usage: show-shelf <reader>* <shelfName>\n");
	}
	std::string username = "";
	std::string shelfName;
	if (params.size() == 2) {
		username = params[0];
		shelfName = params[1];
	}
	else if (params.size() == 1) {
		shelfName = params[0];
	}
	std::shared_ptr<Reader> user;
	if (username == "") {
		user = activeUser;
	}
	else {
		user = goodReads.toReader(goodReads.findUser(username));
	}
	user->showShelf(shelfName);
}