#include "DeleteBookCommand.h"

DeleteBook::DeleteBook(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteBook::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: delete-book <bookName>\n");
	}
	std::string bookName = params[0];
	activeUser->deleteBook(bookName);
}