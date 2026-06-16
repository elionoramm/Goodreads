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
		throw std::logic_error("You must log out before logging into a different account.\n");
	}
	if (activeUser != nullptr && activeUser->getUsername() == username) {
		throw std::logic_error("You are already logged in.\n");
	}
	std::shared_ptr<User> user = goodReads.findUser(username);
	if (user == nullptr) {
		throw std::invalid_argument("Username not found.\n");
	}
	if (user->getPassword() == password) {
		activeUser = user;
		std::cout << "Logged in successfully.\n" << std::endl;
		return;
	}
	std::cout << "Incorrect password.\n" << std::endl;
}