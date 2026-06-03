#include "Commands.h"

// help command
Help::Help(GoodReads& goodReads) : goodReads(goodReads) {}

void Help::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0) {
		throw WrongCommandUsage("Usage: help\n");
	}
	goodReads.help(substrings);
}

// register command
Register::Register(GoodReads& goodReads) : goodReads(goodReads) {}

void Register::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		throw WrongCommandUsage("Usage: register <username> <password> <userType>\n");
	}
	goodReads.registerUser(substrings);
}

// login command
Login::Login(GoodReads& goodReads) : goodReads(goodReads) {}

void Login::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		throw WrongCommandUsage("Usage: login <username> <password>\n");
	}
	goodReads.logIn(substrings);
}

// logout command
Logout::Logout(GoodReads& goodReads) : goodReads(goodReads) {}

void Logout::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0) {
		throw WrongCommandUsage("Usage: logout\n");
	}
	goodReads.logOut(substrings);
}

// exit command
Exit::Exit(GoodReads& goodReads) : goodReads(goodReads) {}

void Exit::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0) {
		throw WrongCommandUsage("Usage: exit\n");
	}
	goodReads.exit(substrings);
}

// Reader commands
// search command
Search::Search(GoodReads& goodReads) : goodReads(goodReads) {}

void Search::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: search <name>\n");
	}
	goodReads.search(substrings);
}

// follow command
Follow::Follow(GoodReads& goodReads) : goodReads(goodReads) {}

void Follow::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: search <name>\n");
	}
	goodReads.follow(substrings);
}

// add-book command
AddBook::AddBook(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBook::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2 && substrings.size() != 3) {
		throw WrongCommandUsage("Usage: add-book <bookName> <status> <rating>*\n");
	}
	goodReads.addBook(substrings);
}

// create-shelf command
CreateShelf::CreateShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void CreateShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: create-shelf <name>\n");
	}
	goodReads.createShelf(substrings);
}

// delete-shelf command
DeleteShelf::DeleteShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: delete-shelf <name>\n");
	}
	goodReads.deleteShelf(substrings);
}

// add-to-shelf command
AddToShelf::AddToShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void AddToShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		throw WrongCommandUsage("Usage: add-to-shelf <bookName> <shelfName>\n");
	}
	goodReads.addToShelf(substrings);
}

// remove-from-shelf command
RemoveFromShelf::RemoveFromShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void RemoveFromShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		throw WrongCommandUsage("Usage: remove-from-shelf <bookName> <shelfName>\n");
	}
	goodReads.removeFromShelf(substrings);
}

// delete-book command
DeleteBook::DeleteBook(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteBook::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: delete-book <bookName>\n");
	}
	goodReads.deleteBook(substrings);
}

// show-shelf command
ShowShelf::ShowShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		throw WrongCommandUsage("Usage: show-shelf <reader>* <shelfName>\n");
	}
	goodReads.showShelf(substrings);
}

// show-inbox command
ShowInbox::ShowInbox(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowInbox::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0 && substrings.size() != 1) {
		throw WrongCommandUsage("Usage: show-inbox <filter>*\n");
	}
	goodReads.showInbox(substrings);
}

// read-msg command
ReadMSG::ReadMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void ReadMSG::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: read-msg <index>\n");
	}
	goodReads.readMessage(substrings);
}

// delete-msg command
DeleteMSG::DeleteMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteMSG::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: delete-msg <index>\n");
	}
	goodReads.deleteMessage(substrings);
}

// friends command
Friends::Friends(GoodReads& goodReads) : goodReads(goodReads) {}

void Friends::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0 && substrings.size() != 1) {
		throw WrongCommandUsage("Usage: friends <reader>*\n");
	}
	goodReads.friends(substrings);
}

// add-birthday command
AddBirthday::AddBirthday(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBirthday::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0 && substrings.size() != 1) {
		throw WrongCommandUsage("Usage: add-birthday <date>*\n");
	}
	goodReads.addBirthday(substrings);
}

// profile command
Profile::Profile(GoodReads& goodReads) : goodReads(goodReads) {}

void Profile::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0 && substrings.size() != 1) {
		throw WrongCommandUsage("Usage: profile <reader>*\n");
	}
	goodReads.profile(substrings);
}

// Author commands
// accept-offer command
AcceptOffer::AcceptOffer(GoodReads& goodReads) : goodReads(goodReads) {}

void AcceptOffer::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: accept-offer <index>\n");
	}
	goodReads.acceptOffer(substrings);
}

// leave command
Leave::Leave(GoodReads& goodReads) : goodReads(goodReads) {}

void Leave::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: leave <publisher>\n");
	}
	goodReads.leave(substrings);
}

// followers command
Followers::Followers(GoodReads& goodReads) : goodReads(goodReads) {}

void Followers::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 0) {
		throw WrongCommandUsage("Usage: followers\n");
	}
	goodReads.followers(substrings);
}

// publisher commands
// publish command
Publish::Publish(GoodReads& goodReads) : goodReads(goodReads) {}

void Publish::execute(std::vector<std::string> substrings) {
	if (substrings.size() < 5) {
		throw WrongCommandUsage("Usage: publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres>\n");
	}
	goodReads.publish(substrings);
}

//add-synopsis command
AddSynopsis::AddSynopsis(GoodReads& goodReads) : goodReads(goodReads) {}

void AddSynopsis::execute(std::vector<std::string> substrings) {
	if (substrings.size() < 2) {
		throw WrongCommandUsage("Usage: add-synopsis <bookTitle> <synopsis>\n");
	}
	goodReads.addSynopsis(substrings);
}

// offer command
Offer::Offer(GoodReads& goodReads) : goodReads(goodReads) {}

void Offer::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		throw WrongCommandUsage("Usage: offer <author>\n");
	}
	goodReads.offer(substrings);
}