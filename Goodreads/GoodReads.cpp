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
	}
	else if (substrings[0] == "register") {
		command = new Register();
	}
	else if (substrings[0] == "login") {
		command = new Login();
	}
	else if (substrings[0] == "logout") {
		command = new Logout();
	}
	else if (substrings[0] == "exit") {
		command = new Exit();
	}
	else if (substrings[0] == "search") {
		command = new Search();
	}
	else if(substrings[0] == "follow") {
		command = new Follow();
	}
	else if (substrings[0] == "add-book") {
		command = new AddBook();
	}
	else if (substrings[0] == "create-shelf") {
		command = new CreateShelf();
	}
	else if (substrings[0] == "delete-shelf") {
		command = new DeleteShelf();
	}
	else if (substrings[0] == "add-to-shelf") {
		command = new AddToShelf();
	}
	else if (substrings[0] == "remove-from-shelf") {
		command = new RemoveFromShelf();
	}
	else if (substrings[0] == "delete-book") {
		command = new DeleteBook();
	}
	else if (substrings[0] == "show-shelf") {
		command = new ShowShelf();
	}
	else if (substrings[0] == "show-inbox") {
		command = new ShowInbox();
	}
	else if (substrings[0] == "read-msg") {
		command = new ReadMSG();
	}
	else if (substrings[0] == "delete-msg") {
		command = new DeleteMSG();
	}
	else if (substrings[0] == "friends") {
		command = new Friends();
	}
	else if (substrings[0] == "add-birthday") {
		command = new AddBirthday();
	}
	else if (substrings[0] == "profile") {
		command = new Profile();
	}
	//else if (substrings[0] == "accept_offer") {
	//	command = new AcceptOffer();
	//}
	//else if (substrings[0] == "leave") {
	//	command = new Leave();
	//}
	//else if (substrings[0] == "followers") {
	//	command = new Followers();
	//}
	//else if (substrings[0] == "publish") {
	//	command = new Publish();
	//}
	//else if (substrings[0] == "add_synopsis") {
	//	command = new AddSynopsis();
	//}
	//else if (substrings[0] == "offer") {
	//	command = new Offer();
	//}
	else {
		std::cout << "Unknown command. Type 'help' for a list of commands.\n" << std::endl;
		return;
	}
	command->execute(substrings);
}