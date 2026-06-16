#include "LeaveCommand.h"

Leave::Leave(GoodReads& goodReads) : goodReads(goodReads) {}

void Leave::execute(std::vector<std::string> params) {
	std::shared_ptr<Author> activeUser = goodReads.getActiveAuthor();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: leave <publisher>\n");
	}
	std::string publisherName = params[0];
	if (activeUser->isWorkingWithPublisher(publisherName) != true) {
		throw std::logic_error("You are not working with this publisher.\n");
	}
	std::shared_ptr<Author> user = goodReads.toAuthor(goodReads.findUser(publisherName));
	if (user == nullptr) {
		throw std::invalid_argument("Publisher not found.\n");
	}
	user->leave(activeUser->getUsername());
	activeUser->leave(user->getUsername());
}