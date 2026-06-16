#include "CommandFactory.h"

CommandFactory::CommandFactory(GoodReads& goodReads) : goodReads(goodReads) {}

std::unique_ptr<Command> CommandFactory::create(const std::string& input) const {
	std::unique_ptr<Command> command = nullptr;
	if (input == "help") {
		command = std::make_unique<Help>(goodReads);
	}
	else if (input == "register") {
		command = std::make_unique<Register>(goodReads);
	}
	else if (input == "login") {
		command = std::make_unique<Login>(goodReads);
	}
	else if (input == "logout") {
		command = std::make_unique<Logout>(goodReads);
	}
	else if (input == "exit") {
		command = std::make_unique<Exit>(goodReads);
	}
	else if (input == "search") {
		command = std::make_unique<Search>(goodReads);
	}
	else if (input == "follow") {
		command = std::make_unique<Follow>(goodReads);
	}
	else if (input == "add-book") {
		command = std::make_unique<AddBook>(goodReads);
	}
	else if (input == "create-shelf") {
		command = std::make_unique<CreateShelf>(goodReads);
	}
	else if (input == "delete-shelf") {
		command = std::make_unique<DeleteShelf>(goodReads);
	}
	else if (input == "add-to-shelf") {
		command = std::make_unique<AddToShelf>(goodReads);
	}
	else if (input == "remove-from-shelf") {
		command = std::make_unique<RemoveFromShelf>(goodReads);
	}
	else if (input == "delete-book") {
		command = std::make_unique<DeleteBook>(goodReads);
	}
	else if (input == "show-shelf") {
		command = std::make_unique<ShowShelf>(goodReads);
	}
	else if (input == "show-inbox") {
		command = std::make_unique<ShowInbox>(goodReads);
	}
	else if (input == "read-msg") {
		command = std::make_unique<ReadMSG>(goodReads);
	}
	else if (input == "delete-msg") {
		command = std::make_unique<DeleteMSG>(goodReads);
	}
	else if (input == "friends") {
		command = std::make_unique<Friends>(goodReads);
	}
	else if (input == "add-birthday") {
		command = std::make_unique<AddBirthday>(goodReads);
	}
	else if (input == "profile") {
		command = std::make_unique<Profile>(goodReads);
	}
	else if (input == "accept-offer") {
		command = std::make_unique<AcceptOffer>(goodReads);
	}
	else if (input == "leave") {
		command = std::make_unique<Leave>(goodReads);
	}
	else if (input == "followers") {
		command = std::make_unique<Followers>(goodReads);
	}
	else if (input == "publish") {
		command = std::make_unique<Publish>(goodReads);
	}
	else if (input == "add-synopsis") {
		command = std::make_unique<AddSynopsis>(goodReads);
	}
	else if (input == "offer") {
		command = std::make_unique<Offer>(goodReads);
	}
	else {
		throw std::logic_error("Unknown command. Type 'help' for a list of commands.\n");
	}
	return command;
}