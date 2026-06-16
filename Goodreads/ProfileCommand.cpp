#include "ProfileCommand.h"

Profile::Profile(GoodReads& goodReads) : goodReads(goodReads) {}

void Profile::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 0 && params.size() != 1) {
		throw WrongCommandUsage("Usage: profile <reader>*\n");
	}
	std::shared_ptr<Reader> user = nullptr;
	if (params.size() == 0) {
		user = activeUser;
	}
	else {
		user = goodReads.toReader(goodReads.findUser(params[0]));
		if (user == nullptr) {
			throw std::invalid_argument("User not found\n");
		}
	}
	std::cout << "Username: " << user->getUsername() << std::endl;
	std::cout << "Birthday: ";
	user->getBirthday().printDate();
	std::cout << std::endl;
	std::cout << "Shelves:\n";
	user->printShelves();
	std::cout << std::endl;
	std::cout << "Favorite Books:\n";
	user->printFavoriteBooks();
	std::cout << std::endl;
	std::cout << "Registered on: ";
	user->getRegistrationDate().printDate();
	std::cout << std::endl;
}