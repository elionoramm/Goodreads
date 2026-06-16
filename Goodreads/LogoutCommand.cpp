#include "LogoutCommand.h"

Logout::Logout(GoodReads& goodReads) : goodReads(goodReads) {}

void Logout::execute(std::vector<std::string> params) {
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 0) {
		throw WrongCommandUsage("Usage: logout\n");
	}
	goodReads.getActiveUser() = nullptr;
	std::cout << "Logged out successfully.\n" << std::endl;
}
