#include "FriendsCommand.h"

Friends::Friends(GoodReads& goodReads) : goodReads(goodReads) {}

void Friends::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 0 && params.size() != 1) {
		throw WrongCommandUsage("Usage: friends <reader>*\n");
	}
	std::shared_ptr<User> targetUser;
	if (params.size() == 1) {
		targetUser = goodReads.findUser(params[0]);
	}
	else {
		targetUser = activeUser;
	}
	int friendCount = 0;
	std::cout << "Friends:\n";
	std::vector<std::shared_ptr<User>> users = goodReads.getUserSystem().getUsers();
	for (auto user : users) {
		if (user->isFollowedBy(targetUser->getUsername()) && targetUser->isFollowedBy(user->getUsername())) {
			std::cout << "- " << user->getUsername() << std::endl;
			friendCount++;
		}
	}
	if (friendCount == 0) {
		std::cout << "This user has no friends yet.\n";
	}
	std::cout << std::endl;
}