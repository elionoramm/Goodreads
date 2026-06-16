#include "ShowInboxCommand.h"

ShowInbox::ShowInbox(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowInbox::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 0 && params.size() != 1) {
		throw WrongCommandUsage("Usage: show-inbox <filter>*\n");
	}
	std::string filter = "";
	if (params.size() == 1) {
		filter = params[0];
	}
	activeUser->showInbox(filter);
	std::cout << std::endl;
}