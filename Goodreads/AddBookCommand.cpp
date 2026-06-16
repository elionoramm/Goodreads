#include "AddBookCommand.h"

AddBook::AddBook(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBook::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 2 && params.size() != 3) {
		throw WrongCommandUsage("Usage: add-book <bookName> <status> <rating>*\n");
	}
	double rating = 0.0;
	if (params.size() == 3) {
		try {
			rating = std::stod(params[2]);
			if (rating > 5 || rating < 1) {
				throw std::invalid_argument("Invalid rating.\n");
			}
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Invalid rating.\n" << std::endl;
			return;
		}
	}
	std::string bookName = params[0];
	std::string status = params[1];
	if (status != "want-to-read" && status != "currently-reading" && status != "paused" && status != "did-not-finish" && status != "read") {
		throw std::invalid_argument("Invalid status.\n");
	}
	std::shared_ptr<Book> book = goodReads.findBook(bookName);
	if (book == nullptr) {
		throw std::invalid_argument("Book not found in the system.\n");
	}
	activeUser->addBook(book, status, rating);
}