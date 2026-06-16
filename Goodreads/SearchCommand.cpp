#include "SearchCommand.h"

Search::Search(GoodReads& goodReads) : goodReads(goodReads) {}

bool Search::fuzzySearch(const std::string& str1, const std::string& str2) const {
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

void Search::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: search <name>\n");
	}
	std::string name = params[0];
	std::cout << "Users:\n";
	unsigned int matches = 0;
	std::vector<std::shared_ptr<User>> users = goodReads.getUserSystem().getUsers();
	for (auto user : users) {
		if (fuzzySearch(user->getUsername(), name)) {
			std::cout << user->getUsername() << " (" << user->getUserType() << ")\n";
			matches++;
		}
	}
	if (matches == 0) {
		std::cout << "No matches found.\n";
	}
	std::cout << "Books:\n";
	matches = 0;
	std::vector<std::shared_ptr<Book>> books = goodReads.getBookSystem().getBooks();
	for (auto book : books) {
		if (fuzzySearch(book->getTitle(), name)) {
			std::cout << book->getTitle() << " (" << book->getAverageRating() << ")" << std::endl;
			matches++;
		}
	}
	if (matches == 0) {
		std::cout << "No matches found.\n";
	}
	std::cout << std::endl;
}