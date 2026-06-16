#include "FollowersCommand.h"

Followers::Followers(GoodReads& goodReads) : goodReads(goodReads) {}

void Followers::execute(std::vector<std::string> substrings) {
	std::shared_ptr<Author> activeUser = goodReads.getActiveAuthor();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (substrings.size() != 0) {
		throw WrongCommandUsage("Usage: followers\n");
	}
	activeUser->printFollowers();
}