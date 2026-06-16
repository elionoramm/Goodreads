#include "FollowCommand.h"

Follow::Follow(GoodReads& goodReads) : goodReads(goodReads) {}

void Follow::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: search <name>\n");
	}
	std::shared_ptr<Reader> user = goodReads.toReader(goodReads.findUser(params[0]));
	if (user == nullptr) {
		throw std::invalid_argument("Username not found.\n");
	}
	std::string activeUserUsername = activeUser->getUsername();
	if (user->getUsername() == activeUserUsername) {
		throw std::invalid_argument("You cannot follow yourself.\n");
	}
	std::string follower = user->findFollower(activeUserUsername);
	if (follower != "") {
		throw std::invalid_argument("You are already following this user.\n");
	}
	user->getFollowers().push_back(activeUserUsername);
	std::cout << "You are now following " << activeUserUsername << ".\n" << std::endl;
	if (user->getUserType() != "publisher") {
		std::string messageContent = activeUserUsername + " has sent you a friend request.";
		Message message = Message(activeUserUsername, 0, messageContent);
		user->receiveMessage(message);
	}
}