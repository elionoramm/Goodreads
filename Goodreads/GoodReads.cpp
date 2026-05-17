#include "GoodReads.h"
std::unique_ptr<GoodReads> GoodReads::instance = std::make_unique<GoodReads>();

void GoodReads::setActiveUser(std::shared_ptr<User> user) {
	instance->activeUser = user;
}

std::shared_ptr<User> GoodReads::getActiveUser() const {
	return instance->activeUser;
}

Repository<User>& GoodReads::getUsers() {
	return instance->users;
}

Repository<Book>& GoodReads::getBooks() {
	return instance->books;
}

void GoodReads::ExecuteCommand(const std::string& line) {
	Command* command;
	std::string word;
	std::vector<std::string> substrings;
	for (int i = 0; i <= line.size(); i++) {
		if (line[i] != ' ' && line[i] != '\0') {
			word = word + line[i];
		}
		else {
			substrings.push_back(word);
			word = "";
		}

	}
	if (substrings[0] == "help") {
		command = new Help();
		command->execute(substrings);
	}
	else if (substrings[0] == "register") {
		command = new Register();
		command->execute(substrings);
	}
	else if (substrings[0] == "login") {
		command = new Login();
		command->execute(substrings);
	}
	else if (substrings[0] == "logout") {
		command = new Logout();
		command->execute(substrings);
	}
	else if (substrings[0] == "exit") {
		command = new Exit();
		command->execute(substrings);
	}
	else if (substrings[0] == "search") {
		command = new Search();
		command->execute(substrings);
	}
	else {
		std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
	}
}