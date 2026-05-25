#include "Commands.h"
#include "Repository.cpp"

// User commands
// Implementing the Help command
Help::Help(GoodReads& goodReads) : goodReads(goodReads) {}

void Help::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		std::cout << "Usage: help\n" << std::endl;
		return;
	}
	goodReads.help();
}

// Implementing the Register command
Register::Register(GoodReads& goodReads) : goodReads(goodReads) {}

void Register::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 4) {
		std::cout << "Usage: register <username> <password> <userType>\n" << std::endl;
		return;
	}
	std::string username = substrings[1];
	std::string password = substrings[2];
	std::string userType = substrings[3];
	goodReads.registerUser(substrings[1], substrings[2], substrings[3]);
}

// Implementing the Login command
Login::Login(GoodReads& goodReads) : goodReads(goodReads) {}

void Login::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		std::cout << "Usage: login <username> <password>\n" << std::endl;
		return;
	}
	goodReads.logIn(substrings[1], substrings[2]);
}

// Implementing the Logout command
Logout::Logout(GoodReads& goodReads) : goodReads(goodReads) {}

void Logout::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		std::cout << "Usage: logout\n" << std::endl;
		return;
	}
	goodReads.logOut();
}

// Implementing the Exit command
Exit::Exit(GoodReads& goodReads) : goodReads(goodReads) {}

void Exit::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		std::cout << "Usage: exit\n" << std::endl;
		return;
	}
	goodReads.exit();
}

// Reader commands
// Implementing the Search command
Search::Search(GoodReads& goodReads) : goodReads(goodReads) {}

void Search::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: search <name>\n" << std::endl;
		return;
	}
	goodReads.search(substrings[1]);
}

// Implementing the Follow command
Follow::Follow(GoodReads& goodReads) : goodReads(goodReads) {}

void Follow::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: search <name>\n" << std::endl;
		return;
	}
	goodReads.follow(substrings[1]);
}

// Implementing the AddBook command
AddBook::AddBook(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBook::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3 && substrings.size() != 4) {
		std::cout << "Usage: add-book <bookName> <status> <rating>*\n" << std::endl;
		return;
	}
	double rating = 0.0;
	if (substrings.size() == 4 && substrings[3] != "") {
		rating = std::stod(substrings[3]);
	}
	std::string bookName = substrings[1];
	std::string status = substrings[2];
	goodReads.addToCollection(bookName, status, rating);
}

// Implementing the CreateShelf command
CreateShelf::CreateShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void CreateShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: create-shelf <name>\n" << std::endl;
		return;
	}
	std::string shelfName = substrings[1];
	goodReads.createShelf(shelfName);
}

// Implementing the DeleteShelf command
DeleteShelf::DeleteShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: delete-shelf <name>\n" << std::endl;
		return;
	}
	std::string shelfName = substrings[1];
	goodReads.deleteShelf(shelfName);
}

// Implementing the AddToShelf command
AddToShelf::AddToShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void AddToShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		std::cout << "Usage: add-to-shelf <bookName> <shelfName>\n" << std::endl;
		return;
	}
	std::string bookName = substrings[1];
	std::string shelfName = substrings[2];
	goodReads.addToShelf(bookName, shelfName);
}

// Implementing the RemoveFromShelf command
RemoveFromShelf::RemoveFromShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void RemoveFromShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		std::cout << "Usage: remove-from-shelf <bookName> <shelfName>\n" << std::endl;
		return;
	}
	std::string bookName = substrings[1];
	std::string shelfName = substrings[2];
	goodReads.removeFromShelf(bookName, shelfName);
}

// Implementing the DeleteBook command
DeleteBook::DeleteBook(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteBook::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: delete-book <bookName>\n" << std::endl;
		return;
	}
	std::string bookName = substrings[1];
	goodReads.deleteBook(bookName);
}

// Implementing the ShowShelf command
ShowShelf::ShowShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2 && substrings.size() != 3) {
		std::cout << "Usage: show-shelf <reader>* <shelfName>\n" << std::endl;
		return;
	}
	std::string username = "";
	std::string shelfName;
	if (substrings.size() == 3) {
		username = substrings[1];
		shelfName = substrings[2];
	}
	else if (substrings.size() == 2) {
		shelfName = substrings[1];
	}
	goodReads.showShelf(username, shelfName);
}

// Implementing the ShowInbox command
ShowInbox::ShowInbox(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowInbox::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		std::cout << "Usage: show-inbox <filter>*\n" << std::endl;
		return;
	}
	std::string filter = "";
	if (substrings.size() == 2) {
		filter = substrings[1];
	}
	goodReads.showInbox(filter);
}

// Implementing the ReadMSG command
ReadMSG::ReadMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void ReadMSG::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: read-msg <index>\n" << std::endl;
		return;
	}
	int index = std::stoi(substrings[1]);
	goodReads.readMessage(index);
}

// Implementing the DeleteMSG command
DeleteMSG::DeleteMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteMSG::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: delete-msg <index>\n" << std::endl;
		return;
	}
	int index = std::stoi(substrings[1]);
	goodReads.deleteMessage(index);
}

// Implementing the Friends command
Friends::Friends(GoodReads& goodReads) : goodReads(goodReads) {}

void Friends::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		std::cout << "Usage: friends <reader>*\n" << std::endl;
		return;
	}
	std::string username = "";
	if (substrings.size() == 2) {
		username = substrings[1];
	}
	goodReads.friends(username);
}

// Implementing the AddBirthday command
AddBirthday::AddBirthday(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBirthday::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		std::cout << "Usage: add-birthday <date>*\n" << std::endl;
		return;
	}
	Date birthday;
	if (substrings.size() == 1) {
		birthday = Date();
	}
	else if (substrings.size() == 2) {
		birthday = Date(substrings[1]);
	}
	goodReads.addBirthday(birthday);
}

// Implementing the Profile command
Profile::Profile(GoodReads& goodReads) : goodReads(goodReads) {}

void Profile::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		std::cout << "Usage: profile <reader>*\n" << std::endl;
		return;
	}
	std::string username;
	if (substrings.size() == 1) {
		username = "";
	}
	else {
		username = substrings[1];
	}
	goodReads.profile(username);
}

// Author commands
// Implementing the AcceptOffer command
AcceptOffer::AcceptOffer(GoodReads& goodReads) : goodReads(goodReads) {}

void AcceptOffer::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: accept-offer <index>\n" << std::endl;
		return;
	}
	int index = std::stoi(substrings[1]);
	goodReads.acceptOffer(index);
}

// Implementing the Leave command
Leave::Leave(GoodReads& goodReads) : goodReads(goodReads) {}

void Leave::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: leave <publisher>\n" << std::endl;
		return;
	}
	std::string publisherName = substrings[1];
	goodReads.leave(publisherName);
}

// Implementing the Followers command
Followers::Followers(GoodReads& goodReads) : goodReads(goodReads) {}

void Followers::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		std::cout << "Usage: followers\n" << std::endl;
		return;
	}
	goodReads.followers();
}

// Publisher commands
// Implementing the Publish command
Publish::Publish(GoodReads& goodReads) : goodReads(goodReads) {}

void Publish::execute(std::vector<std::string> substrings) {
	if (substrings.size() < 6) {
		std::cout << "Usage: publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres>\n" << std::endl;
		return;
	}
	std::string bookTitle = substrings[1];
	std::string authorName = substrings[2];
	Date releaseDate = Date(substrings[3]);
	int pageCount = std::stoi(substrings[4]);
	std::vector<std::string> genres;
	for (int i = 5; i < substrings.size(); i++) {
		genres.push_back(substrings[i]);
	}
	goodReads.publish(bookTitle, authorName, releaseDate, pageCount, genres);
}

// Implementing the AddSynopsis command
AddSynopsis::AddSynopsis(GoodReads& goodReads) : goodReads(goodReads) {}

void AddSynopsis::execute(std::vector<std::string> substrings) {
	if (substrings.size() < 3) {
		std::cout << "Usage: add-synopsis <bookTitle> <synopsis>\n" << std::endl;
		return;
	}
	std::string bookTitle = substrings[1];
	std::string synopsis = "";
	for (size_t i = 2; i < substrings.size(); i++) {
		synopsis = synopsis + substrings[i] + " ";
	}
	goodReads.addSynopsis(bookTitle, synopsis);
}

//Implementing the Offer command
Offer::Offer(GoodReads& goodReads) : goodReads(goodReads) {}

void Offer::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: offer <author>\n" << std::endl;
		return;
	}
	std::string authorName = substrings[1];
	goodReads.offer(authorName);
}