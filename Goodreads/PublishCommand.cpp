#include "PublishCommand.h"

Publish::Publish(GoodReads& goodReads) : goodReads(goodReads) {}

void Publish::execute(std::vector<std::string> params) {
	std::shared_ptr<Publisher> activeUser = goodReads.getActivePublisher();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() < 5) {
		throw WrongCommandUsage("Usage: publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres>\n");
	}
	std::string bookName = params[0];
	std::string authorName = params[1];
	Date releaseDate;
	int pageCount;
	try {
		releaseDate = Date(params[2]);
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
		return;
	}
	try {
		pageCount = std::stoi(params[3]);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid page count.\n" << std::endl;
		return;
	}
	std::vector<std::string> genres;
	for (int i = 4; i < params.size(); i++) {
		genres.push_back(params[i]);
	}
	std::shared_ptr<Book> book = goodReads.findBook(bookName);
	if (book != nullptr) {
		throw std::invalid_argument("Book with this title already exists.\n");
	}
	std::shared_ptr<Author> author = goodReads.toAuthor(goodReads.findUser(authorName));
	if (!activeUser->isWorkingWithAuthor(authorName)) {
		throw std::invalid_argument("You are not working with this author you cannot publish their book.\n");
	}
	std::shared_ptr<Book> newBook = std::make_shared<Book>(bookName, authorName, activeUser->getUsername(), releaseDate, pageCount, genres);
	std::cout << "You have successfully published the book " << bookName << "\n" << std::endl;
	std::string activeUserUsername = activeUser->getUsername();
	std::vector<std::shared_ptr<User>> users = goodReads.getUserSystem().getUsers();
	for (size_t i = 0; i < users.size(); i++) {
		std::string messageContent = "";
		if (author->isFollowedBy(users[i]->getUsername()) && activeUser->isFollowedBy(users[i]->getUsername())) {
			messageContent = "New book published by author " + authorName + " and publisher " + activeUser->getUsername() + ": " + bookName;
		}
		else if (author->isFollowedBy(users[i]->getUsername())) {
			messageContent = "New book published by author " + authorName + ": " + bookName;
		}
		else if (activeUser->isFollowedBy(users[i]->getUsername())) {
			messageContent = "New book published by publisher" + activeUser->getUsername() + ": " + bookName;
		}
		if (messageContent != "") {
			Message message = Message(activeUserUsername, 0, messageContent);
			goodReads.toReader(users[i])->receiveMessage(message);
		}
	}
	goodReads.getBookSystem().addBook(newBook);
	activeUser->addToPublishedBooks(newBook);
	author->addToPublishedBooks(newBook);
}