#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GoodReads.h"
#include "Reader.h"
#include "Book.h"
#include "Command.h"
#include "Commands.h"
int main()
{
	GoodReads goodReads;
	goodReads.registerUser("eli", "pass", "reader");
	goodReads.registerUser("eli1", "pass", "author");
	goodReads.registerUser("eli2", "pass", "publisher");
	goodReads.logIn("eli2", "pass");
	std::vector<std::string> genres;
	goodReads.publish("book", "eli1", Date(), 100, genres);
	goodReads.addSynopsis("book", "Bookish book about book things.");
	while (true) {
		std::string line;
		std::cout << "Enter command: ";
		std::getline(std::cin, line);
		std::unique_ptr<Command> command = nullptr;
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
			command = std::make_unique<Help>(goodReads);
		}
		else if (substrings[0] == "register") {
			command = std::make_unique<Register>(goodReads);
		}
		else if (substrings[0] == "login") {
			command = std::make_unique<Login>(goodReads);
		}
		else if (substrings[0] == "logout") {
			command = std::make_unique<Logout>(goodReads);
		}
		else if (substrings[0] == "exit") {
			command = std::make_unique<Exit>(goodReads);
		}
		else if (substrings[0] == "search") {
			command = std::make_unique<Search>(goodReads);
		}
		else if (substrings[0] == "follow") {
			command = std::make_unique<Follow>(goodReads);
		}
		else if (substrings[0] == "add-book") {
			command = std::make_unique<AddBook>(goodReads);
		}
		else if (substrings[0] == "create-shelf") {
			command = std::make_unique<CreateShelf>(goodReads);
		}
		else if (substrings[0] == "delete-shelf") {
			command = std::make_unique<DeleteShelf>(goodReads);
		}
		else if (substrings[0] == "add-to-shelf") {
			command = std::make_unique<AddToShelf>(goodReads);
		}
		else if (substrings[0] == "remove-from-shelf") {
			command = std::make_unique<RemoveFromShelf>(goodReads);
		}
		else if (substrings[0] == "delete-book") {
			command = std::make_unique<DeleteBook>(goodReads);
		}
		else if (substrings[0] == "show-shelf") {
			command = std::make_unique<ShowShelf>(goodReads);
		}
		else if (substrings[0] == "show-inbox") {
			command = std::make_unique<ShowInbox>(goodReads);
		}
		else if (substrings[0] == "read-msg") {
			command = std::make_unique<ReadMSG>(goodReads);
		}
		else if (substrings[0] == "delete-msg") {
			command = std::make_unique<DeleteMSG>(goodReads);
		}
		else if (substrings[0] == "friends") {
			command = std::make_unique<Friends>(goodReads);
		}
		else if (substrings[0] == "add-birthday") {
			command = std::make_unique<AddBirthday>(goodReads);
		}
		else if (substrings[0] == "profile") {
			command = std::make_unique<Profile>(goodReads);
		}
		else if (substrings[0] == "accept-offer") {
			command = std::make_unique<AcceptOffer>(goodReads);
		}
		else if (substrings[0] == "leave") {
			command = std::make_unique<Leave>(goodReads);
		}
		else if (substrings[0] == "followers") {
			command = std::make_unique<Followers>(goodReads);
		}
		else if (substrings[0] == "publish") {
			command = std::make_unique<Publish>(goodReads);
		}
		else if (substrings[0] == "add-synopsis") {
			command = std::make_unique<AddSynopsis>(goodReads);
		}
		else if (substrings[0] == "offer") {
			command = std::make_unique<Offer>(goodReads);
		}
		else {
			std::cout << "Unknown command. Type 'help' for a list of commands.\n" << std::endl;
			continue;
		}
		command->execute(substrings);
	}
}