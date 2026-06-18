#include <iostream>
#include "Reader.h"

Reader::Reader(const std::string& username, const std::string& password) : User(username, password) {}

void Reader::loadUser(std::fstream& file, const BookSystem& bookSystem) {
	User::loadUser(file, bookSystem);
	// loading the profile books
	std::string profileBooksCount;
	file >> profileBooksCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(profileBooksCount)); i++) {
		std::string bookTitle;
		file >> bookTitle;
		std::string status;
		double rating;
		file >> status >> rating;
		profileBooks.push_back(std::make_tuple(bookSystem.findBook(bookTitle), status, rating));
	}
	// loading the shelf books
	std::string shelvesCount;
	file >> shelvesCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(shelvesCount)); i++) {
		std::string shelfName;
		file >> shelfName;
		shelves.push_back(Shelf(shelfName));
		std::string shelfBooksCount;
		file >> shelfBooksCount;
		for (size_t i = 0; i < static_cast<size_t>(std::stoull(shelfBooksCount)); i++) {
			std::string bookTitle;
			file >> bookTitle;
			shelves[i].addBook(bookSystem.findBook(bookTitle));
		}
	}
	// loading the favorite books
	std::string favoriteBooksCount;
	file >> favoriteBooksCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(favoriteBooksCount)); i++) {
		std::string bookTitle;
		file >> bookTitle;
		favoriteBooks.push_back(bookSystem.findBook(bookTitle));
	}
	// loading the birthday
	std::string birthdayString;
	file >> birthdayString;
	birthday = Date(birthdayString);
	// loading the inbox
	std::string inboxCount;
	file >> inboxCount;
	for (size_t i = 0; i < static_cast<size_t>(std::stoull(inboxCount)); i++) {
		std::string messenger, messageContent;
		std::string status;
		file >> messenger;
		file >> status;
		std::getline(file >> std::ws, messageContent);
		Message message = Message(messenger, stoi(status), messageContent);
		inbox.push_back(message);
	}
}

void Reader::saveUser(std::fstream& file) const {
	// saving the profile books
	User::saveUser(file);
	file << std::to_string(profileBooks.size()) << '\n';
	for (const auto& [profileBook, status, rating] : profileBooks) {
		file << profileBook->getTitle() << '\n';
		file << status << '\n';
		file << std::to_string(rating) << '\n';
	}
	// saving the shelf books
	file << std::to_string(shelves.size()) << '\n';
	for (size_t i = 0; i < shelves.size(); i++) {
		file << shelves[i].getName() << '\n' << std::to_string(shelves[i].size()) << '\n';
		for (size_t j = 0; j < shelves[i].size(); j++) {
			file << shelves[i][j]->getTitle() << '\n';
		}
	}
	// saving the favorite books
	file << std::to_string(favoriteBooks.size()) << '\n';
	for (size_t i = 0; i < favoriteBooks.size(); i++) {
		file << favoriteBooks[i]->getTitle() << '\n';
	}
	// saving the birthday
	file << birthday.dateToString() << '\n';
	// saving the inbox
	file << std::to_string(inbox.size()) << '\n';
	for (size_t i = 0; i < inbox.size(); i++) {
		inbox[i].saveMessage(file);
	}
}

std::string Reader::getUserType() const {
	return "reader";
}

void Reader::help() const {
	std::cout << "register <username> <password> <userType>\n"
		"login <username> <password>\n"
		"logout\n"
		"exit\n"
		"search <name>\n"
		"follow <username>\n"
		"add-book <bookName> <status> <rating>*\n"
		"create-shelf <name>\n"
		"delete-shelf <name>\n"
		"add-to-shelf <bookName> <shelfName>\n"
		"remove-from-shelf <bookName> <shelfName>\n"
		"delete-book <bookName>\n"
		"show-shelf <reader>* <shelfName>\n"
		"show-inbox <filter>*\n"
		"read-msg <index>\n"
		"delete-msg <index>\n"
		"friends <reader>*\n"
		"add-birthday <date>*\n"
		"profile <reader>*\n";
}

void Reader::addBook(const std::shared_ptr<Book>& book, const std::string& status, const double rating) {
	for (auto& [profileBook, currentStatus, currentRrating] : profileBooks) {
		if (profileBook->getTitle() == book->getTitle()) {
			if (currentRrating != 0 && rating != 0) {
				std::cout << "You have already given this book a rating.\n" << std::endl;
			}
			if (currentRrating == 0 && rating > 8) {
				favoriteBooks.push_back(book);
			}
			if (currentRrating == 0 && rating != 0) {
				book->addReview(rating);
				currentRrating = rating;
				std::cout << "You have added a rating to book " << book->getTitle() << std::endl;
			}
			if (currentStatus == status) {
				std::cout << "Book already exists in your profile with this status.\n" << std::endl;
				return;
			}
			else if (currentStatus != status) {
				currentStatus = status;
				std::cout << "Changed the status of book " << profileBook->getTitle() << " to " << status << ".\n" << std::endl;
				return;
			}
		}
	}
	std::shared_ptr<Book> newBook = std::make_shared<Book>(book->getTitle(), book->getAuthor(), book->getPublisher(), book->getReleaseDate(), book->getPageCount(), book->getGenres());
	profileBooks.push_back(make_tuple(newBook, status, rating));
	std::cout << "Book '" << book->getTitle() << "' added to your profile with status '" << status << "'";
	if (rating != 0) {
		std::cout << " and rating " << rating;
		book->addReview(rating);
		if (rating > 8) {
			favoriteBooks.push_back(book);
		}
	}
	std::cout << "\n" << std::endl;
}

void Reader::createShelf(const std::string& shelfName) {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i].getName() == shelfName) {
			throw std::invalid_argument("A shelf with this name already exists.\n");
		}
	}
	shelves.push_back(Shelf(shelfName));
	std::cout << "Shelf '" << shelfName << "' created successfully.\n" << std::endl;
}

void Reader::deleteShelf(const std::string& shelfName) {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i].getName() == shelfName) {
			shelves.erase(shelves.begin() + i);
			std::cout << "Shelf '" << shelfName << "' deleted.\n" << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::addToShelf(const std::shared_ptr<Book>& book, const std::string& shelfName) {
	std::shared_ptr<Book> newBook = std::make_shared<Book>(book->getTitle(), book->getAuthor(), book->getPublisher(), book->getReleaseDate(), book->getPageCount(), book->getGenres());
	newBook->addSynopsis(book->getSynopsis());
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i].getName() == shelfName) {
			if(shelves[i].addBook(newBook)){
				std::cout << "Book '" << book->getTitle() << "' added to shelf '" << shelfName << "'\n" << std::endl;
				return;
			}
			std::cout << "Book is already on that shelf.\n" << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::removeFromShelf(const std::string& bookName, const std::string& shelfName) {
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i].getName() == shelfName) {
			if(shelves[i].removeBook(bookName)){
				return;
			}
			std::cout << "Book not found on that shelf.\n" << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::deleteBook(const std::string& bookName) {
	bool deleted = false;
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i].removeBook(bookName)) {
			deleted = true;
		}
	}
	for (size_t i = 0; i < favoriteBooks.size(); i++) {
		if (favoriteBooks[i]->getTitle() == bookName) {
			favoriteBooks.erase(favoriteBooks.begin() + i);
			std::cout << "Book '" << bookName << "' removed from favorite books.\n";
		}
	}
	for (size_t i = 0; i < profileBooks.size(); i++) {
		const auto& [profileBook, currentStatus, currentRating] = profileBooks[i];
		if (profileBook->getTitle() == bookName) {
			profileBooks.erase(profileBooks.begin() + i);
			std::cout << "Book '" << bookName << "' removed from your profile.\n" << std::endl;
			return;
		}
	}
	if (!deleted) {
		std::cout << "Book not found in your profile.\n" << std::endl;
	}
	std::cout << std::endl;
}

void Reader::showShelf(const std::string& shelfName) const {
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i].getName() == shelfName) {
			std::cout << "Books in shelf '" << shelfName << "':\n";
			shelves[i].printShelf();
			std::cout << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

void Reader::showInbox(const std::string& filter) const {
	if(inbox.size() == 0) {
		std::cout << "Your inbox is empty.\n";
		return;
	}
	if (filter != "friends") {
		std::cout << "Messages in your inbox:\n";
		for (size_t i = 0; i < inbox.size(); i++) {
			std::cout << i + 1 << ". from: " << inbox[i].getMessenger() << ", status : " << (inbox[i].getStatus() ? "read" : "unread") << "\n";
		}
	}
	else {
		std::cout << "Friend requests in your inbox:\n";
		for (size_t i = 0; i < inbox.size(); i++) {
			if (inbox[i].getMessageContent().find("has sent you a friend request") != std::string::npos) {
				std::cout << i + 1 << ". " << inbox[i].getMessageContent() << " (from: " << inbox[i].getMessenger() << ", status: " << (inbox[i].getStatus() ? "read" : "unread") << ")\n";
			}
		}
	}
}

void Reader::receiveMessage(const Message& message) {
	inbox.push_back(message);
}

void Reader::readMessage(const size_t& index) {
	if (index < 1 || index > inbox.size()) {
		std::cout << "Invalid message index.\n" << std::endl;
		return;
	}
	Message message = inbox[index - 1];
	std::cout << message.getMessageContent() << "\n" << std::endl;
	inbox[index - 1].markAsRead();
}

void Reader::deleteMessage(const size_t& index) {
	if (index < 1 || index > inbox.size()) {
		std::cout << "Invalid message index.\n" << std::endl;
		return;
	}
	inbox.erase(inbox.begin() + index - 1);
	std::cout << "Message deleted.\n" << std::endl;
}

void Reader::setBirthday(const Date& date) {
	if (birthday.isSet() && !date.isSet()) {
		std::cout << "Birthday erased successfully.\n" << std::endl;
		birthday = date;
		return;
	}
	if (birthday.isSet() && date.isSet()) {
		std::cout << "Birthday changed successfully.\n" << std::endl;
	}
	else if (date.isSet()) {
		std::cout << "Birthday added successfully.\n" << std::endl;
	}
	this->birthday = date;
}

Date Reader::getBirthday() const {
	return birthday;
}

void Reader::printShelves() const {
	if (shelves.size() == 0) {
		std::cout << "No shelves in this profile.\n";
		return;
	}
	for (size_t i = 0; i < shelves.size(); i++) {
		std::cout << shelves[i].getName() << ":\n";
		shelves[i].printShelf();
	}
}

void Reader::printFavoriteBooks() const {
	if (favoriteBooks.size() == 0) {
		std::cout << "No favorite books in this profile." << std::endl;
		return;
	}
	std::cout << "Your favorite books:\n";
	for (size_t i = 0; i < favoriteBooks.size(); i++) {
		std::cout << "- " << favoriteBooks[i] << "\n";
	}
}