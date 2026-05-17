#include "Commands.h"
#include "Repository.cpp"

// Implementing the Help command
void Help::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		std::cout << "Usage: help\n" << std::endl;
		return;
	}
	if(GoodReads::instance->getActiveUser() == nullptr) {
		std::cout << "No user is currently logged in.\n" << std::endl;
		return;
	}
	auto activeUser = GoodReads::instance->getActiveUser();
	std::string userType = activeUser->getUserType();
	std::cout << "register <username> <password> <userType>\n"
		"login <username> <password>\n"
		"logout\n"
		"exit\n";
	if (userType == "Reader" || userType == "Author") {
		std::cout << "search <name>\n"
			"follow <username>\n"
			"add_book <bookName> <status> <rating>*\n"
			"create_shelf <name>\n"
			"delete_shelf <name>\n"
			"add_to_shelf <bookName> <shelfName>\n"
			"remove_from_shelf <bookName> <shelfName>\n"
			"delete_book <bookName>\n"
			"show_shelf <reader>* <shelfName>\n"
			"show_inbox <filter>*\n"
			"read_msg <index>\n"
			"delete_msg <index>\n"
			"friends <reader>*\n"
			"add_birthday <date>*\n"
			"profile <reader>*\n";
	}
	if (userType == "Author") {
		std::cout << "accept_offer <index>\n"
			"leave <publisher>\n"
			"followers\n";
	}
	if (userType == "Publisher") {
		std::cout << "publish <book_title>\n"
			"add_synopsis <book_title> <synopsis>\n"
			"offer <author_username> <book_title> <synopsis>\n" << std::endl;
	}
}

// Implementing the Register command
void Register::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 4) {
		std::cout << "Usage: register <username> <password> <userType>\n" << std::endl;
		return;
	}
	else {
		std::string username = substrings[1];
		std::string password = substrings[2];
		std::string userType = substrings[3];
		Repository<User> users = GoodReads::instance->getUsers();
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == username) {
				std::cout << "Username already exists.\n" << std::endl;
				return;
			}
		}
		std::shared_ptr<User> newUser;
		if (userType == "reader") {
			newUser = std::make_shared<Reader>(username, password);
		}
		else if (userType == "author") {
			newUser = std::make_shared<Author>(username, password);
		}
		else if (userType == "publisher") {
			newUser = std::make_shared<Publisher>(username, password);
		}
		else {
			std::cout << "Invalid user type. Must be 'reader', 'author', or 'publisher'.\n" << std::endl;
			return;
		}

		GoodReads::instance->getUsers().addElement(newUser);
		std::cout << "User registered successfully!\n" << std::endl;
		GoodReads::instance->setActiveUser(newUser);
		std::cout << "You are now logged in as " << username << ".\n" << std::endl;
		std::cout << GoodReads::instance->getUsers().size() << std::endl;
	}
}

// Implementing the Login command
void Login::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		std::cout << "Usage: login <username> <password>\n" << std::endl;
		return;
	}
	std::string username = substrings[1];
	std::string password = substrings[2];
	Repository<User> users = GoodReads::instance->getUsers();
	std::cout << users.size() << std::endl;
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			if (users[i]->getPassword() == password) {
				GoodReads::instance->setActiveUser(users[i]);
				std::cout << "Logged in successfully!\n" << std::endl;
				return;
			}
			else {
				std::cout << "Incorrect password.\n" << std::endl;
				return;
			}
		}
	}
	std::cout << "Username not found.\n" << std::endl;
}

// Implementing the Logout command
void Logout::execute(std::vector<std::string> substrings) {
	if (GoodReads::instance->getActiveUser() == nullptr) {
		std::cout << "No user is currently logged in.\n" << std::endl;
		return;
	}
	GoodReads::instance->setActiveUser(nullptr);
	std::cout << "Logged out successfully.\n" << std::endl;
}

// Implementing the Exit command
void Exit::execute(std::vector<std::string> substrings) {
	std::cout << "Exiting the application. Goodbye!" << std::endl;
	exit(0);
}

// Implementing the Search command
bool Search::caseInsensitiveMatch(const std::string& str1, const std::string& str2) {
	if (str1.size() != str2.size()) {
		return false;
	}
	unsigned int differences = 0;
	for (size_t i = 0; i < str1.size() && i < str2.size(); i++) {
		if (tolower(str1[i]) != tolower(str2[i])) {
			differences++;
		}
	}
	return differences <= 2;
}

void Search::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: search <name>\n" << std::endl;
		return;
	}
	std::string name = substrings[1];
	Repository<User> users = GoodReads::instance->getUsers();
	Repository<Book> books = GoodReads::instance->getBooks();
	std::cout << "Users:\n";
	unsigned int matches = 0;
	for (size_t i = 0; i < users.size(); i++) {
		if (caseInsensitiveMatch(users[i]->getUsername(), name)) {
			std::cout << users[i]->getUsername() << " (" << users[i]->getUserType() << ")\n";
			matches++;
		}
	}
	if (matches == 0) {
		std::cout << "No matches found.\n";
	}
	std::cout << "Books:\n";
	matches = 0;
	for (size_t i = 0; i < books.size(); i++) {
		if (caseInsensitiveMatch(books[i]->getTitle(), name)) {
			std::cout << books[i]->getTitle() << " (" << books[i]->getAverageRating() << ")\n";
			matches++;
		}
	}
	if (matches == 0) {
		std::cout << "No matches found.\n" << std::endl;
	}
}

// Implementing the Follow command
void Follow::execute(std::vector<std::string> substrings) {

}