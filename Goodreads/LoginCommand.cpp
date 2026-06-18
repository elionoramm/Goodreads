#include "LoginCommand.h"

Login::Login(GoodReads& goodReads) : goodReads(goodReads) {}

void Login::execute(std::vector<std::string> params) {
	if (params.size() != 2) {
		throw WrongCommandUsage("Usage: login <username> <password>\n");
	}
	std::shared_ptr<User> activeUser = goodReads.getActiveUser();
	std::string username = params[0];
	std::string password = params[1];
	if (activeUser != nullptr) {
		if (activeUser->getUsername() == username) {
			throw std::logic_error("You are already logged in.\n");
		}
		throw std::logic_error("You must log out before logging into a different account.\n");
	}
	std::shared_ptr<User> user = goodReads.findUser(username);
	if (user->getPassword() == password) {
		goodReads.setActiveUser(user);
		std::cout << "Logged in successfully.\n" << std::endl;
		return;
	}
	std::cout << "Incorrect password.\n" << std::endl;
}