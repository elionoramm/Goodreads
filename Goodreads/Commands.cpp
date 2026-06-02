#include "Commands.h"

// User commands
// Implementing the Help command
Help::Help(GoodReads& goodReads) : goodReads(goodReads) {}

void Help::execute(std::vector<std::string> substrings) {
	goodReads.help(substrings);
}

// Implementing the Register command
Register::Register(GoodReads& goodReads) : goodReads(goodReads) {}

void Register::execute(std::vector<std::string> substrings) {
	goodReads.registerUser(substrings);
}

// Implementing the Login command
Login::Login(GoodReads& goodReads) : goodReads(goodReads) {}

void Login::execute(std::vector<std::string> substrings) {
	goodReads.logIn(substrings);
}

// Implementing the Logout command
Logout::Logout(GoodReads& goodReads) : goodReads(goodReads) {}

void Logout::execute(std::vector<std::string> substrings) {
	goodReads.logOut(substrings);
}

// Implementing the Exit command
Exit::Exit(GoodReads& goodReads) : goodReads(goodReads) {}

void Exit::execute(std::vector<std::string> substrings) {
	goodReads.exit(substrings);
}

// Reader commands
// Implementing the Search command
Search::Search(GoodReads& goodReads) : goodReads(goodReads) {}

void Search::execute(std::vector<std::string> substrings) {
	goodReads.search(substrings);
}

// Implementing the Follow command
Follow::Follow(GoodReads& goodReads) : goodReads(goodReads) {}

void Follow::execute(std::vector<std::string> substrings) {
	goodReads.follow(substrings);
}

// Implementing the AddBook command
AddBook::AddBook(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBook::execute(std::vector<std::string> substrings) {
	goodReads.addToCollection(substrings);
}

// Implementing the CreateShelf command
CreateShelf::CreateShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void CreateShelf::execute(std::vector<std::string> substrings) {
	goodReads.createShelf(substrings);
}

// Implementing the DeleteShelf command
DeleteShelf::DeleteShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteShelf::execute(std::vector<std::string> substrings) {
	goodReads.deleteShelf(substrings);
}

// Implementing the AddToShelf command
AddToShelf::AddToShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void AddToShelf::execute(std::vector<std::string> substrings) {
	goodReads.addToShelf(substrings);
}

// Implementing the RemoveFromShelf command
RemoveFromShelf::RemoveFromShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void RemoveFromShelf::execute(std::vector<std::string> substrings) {
	goodReads.removeFromShelf(substrings);
}

// Implementing the DeleteBook command
DeleteBook::DeleteBook(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteBook::execute(std::vector<std::string> substrings) {
	goodReads.deleteBook(substrings);
}

// Implementing the ShowShelf command
ShowShelf::ShowShelf(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowShelf::execute(std::vector<std::string> substrings) {
	goodReads.showShelf(substrings);
}

// Implementing the ShowInbox command
ShowInbox::ShowInbox(GoodReads& goodReads) : goodReads(goodReads) {}

void ShowInbox::execute(std::vector<std::string> substrings) {
	goodReads.showInbox(substrings);
}

// Implementing the ReadMSG command
ReadMSG::ReadMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void ReadMSG::execute(std::vector<std::string> substrings) {
	goodReads.readMessage(substrings);
}

// Implementing the DeleteMSG command
DeleteMSG::DeleteMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteMSG::execute(std::vector<std::string> substrings) {
	goodReads.deleteMessage(substrings);
}

// Implementing the Friends command
Friends::Friends(GoodReads& goodReads) : goodReads(goodReads) {}

void Friends::execute(std::vector<std::string> substrings) {
	goodReads.friends(substrings);
}

// Implementing the AddBirthday command
AddBirthday::AddBirthday(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBirthday::execute(std::vector<std::string> substrings) {
	goodReads.addBirthday(substrings);
}

// Implementing the Profile command
Profile::Profile(GoodReads& goodReads) : goodReads(goodReads) {}

void Profile::execute(std::vector<std::string> substrings) {
	goodReads.profile(substrings);
}

// Author commands
// Implementing the AcceptOffer command
AcceptOffer::AcceptOffer(GoodReads& goodReads) : goodReads(goodReads) {}

void AcceptOffer::execute(std::vector<std::string> substrings) {
	goodReads.acceptOffer(substrings);
}

// Implementing the Leave command
Leave::Leave(GoodReads& goodReads) : goodReads(goodReads) {}

void Leave::execute(std::vector<std::string> substrings) {
	goodReads.leave(substrings);
}

// Implementing the Followers command
Followers::Followers(GoodReads& goodReads) : goodReads(goodReads) {}

void Followers::execute(std::vector<std::string> substrings) {
	goodReads.followers(substrings);
}

// Publisher commands
// Implementing the Publish command
Publish::Publish(GoodReads& goodReads) : goodReads(goodReads) {}

void Publish::execute(std::vector<std::string> substrings) {
	goodReads.publish(substrings);
}

// Implementing the AddSynopsis command
AddSynopsis::AddSynopsis(GoodReads& goodReads) : goodReads(goodReads) {}

void AddSynopsis::execute(std::vector<std::string> substrings) {
	goodReads.addSynopsis(substrings);
}

//Implementing the Offer command
Offer::Offer(GoodReads& goodReads) : goodReads(goodReads) {}

void Offer::execute(std::vector<std::string> substrings) {
	goodReads.offer(substrings);
}