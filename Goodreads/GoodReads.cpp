#include "GoodReads.h"

void GoodReads::help() const {
	if (activeUser == nullptr) {
		std::cout << "No user is currently logged in.\n" << std::endl;
		return;
	}activeUser->help();
}

void GoodReads::registerUser(const std::string& username, const std::string& password, const std::string& role) {
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			std::cout << "Username already exists.\n" << std::endl;
			return;
		}
	}
	std::shared_ptr<User> newUser;
	if (role == "reader") {
		newUser = std::make_shared<Reader>(username, password);
	}
	else if (role == "author") {
		newUser = std::make_shared<Author>(username, password);
	}
	else if (role == "publisher") {
		newUser = std::make_shared<Publisher>(username, password);
	}
	else {
		std::cout << "Invalid user type. Must be 'reader', 'author', or 'publisher'.\n" << std::endl;
		return;
	}
	users.push_back(newUser);
	std::cout << "User registered successfully!\n" << std::endl;
}

void GoodReads::logIn(const std::string& username, const std::string& password) {
	if (activeUser != nullptr && activeUser->getUsername() == username) {
		std::cout << "You are already logged in.\n" << std::endl;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			if (users[i]->getPassword() == password) {
				activeUser = users[i];
				std::cout << "Logged in successfully!\n" << std::endl;
				return;
			}
			else {
				std::cout << "Incorrect password.\n" << std::endl;
				return;
			}
		}
	}
	std::cout << "Username not found.\n" << std::endl;
}

void GoodReads::logOut() {
	if (activeUser == nullptr) {
		std::cout << "No user is currently logged in.\n" << std::endl;
		return;
	}
	activeUser = nullptr;
	std::cout << "Logged out successfully.\n" << std::endl;
}
// WIP
void GoodReads::exit() {
	// save data to file
	std::cout << "Exiting the application. Goodbye!\n" << std::endl;
	std::exit(0);
}

bool GoodReads::caseInsensitiveMatch(const std::string& str1, const std::string& str2) const {
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

void GoodReads::search(const std::string& name) const {
	std::cout << "Users:\n";
	unsigned int matches = 0;
	for (size_t i = 0; i < users.size(); i++) {
		if (caseInsensitiveMatch(users[i]->getUsername(), name)) {
			std::cout << users[i]->getUsername() << " (" << users[i]->getUserType() << ")\n";
			matches++;
		}
	}
	if (matches == 0) {
		std::cout << "No matches found.\n";
	}
	std::cout << "Books:\n";
	matches = 0;
	for (size_t i = 0; i < books.size(); i++) {
		if (caseInsensitiveMatch(books[i]->getTitle(), name)) {
			std::cout << books[i]->getTitle() << " (" << books[i]->getAverageRating() << ")\n";
			matches++;
		}
	}
	if (matches == 0) {
		std::cout << "No matches found.\n" << std::endl;
	}
}

void GoodReads::follow(const std::string& username) {
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to follow someone.\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			users[i]->addFollower(activeUser);
			return;
		}
	}
	std::cout << "Username not found.\n" << std::endl;
}

void GoodReads::addToCollection(const std::string& bookName, const std::string& status, double rating) {
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to add a book.\n" << std::endl;
		return;
	}
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i]->getTitle() == bookName) {
			book = books[i];
			break;
		}
	}
	if (book == nullptr) {
		std::cout << "Book not found in the repository.\n" << std::endl;
		return;
	}
	activeUser->addToCollection(book, status, rating);
}

void GoodReads::createShelf(const std::string& shelfName) {
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to create a shelf.\n" << std::endl;
		return;
	}
	activeUser->createShelf(shelfName);
}

void GoodReads::deleteShelf(const std::string& shelfName) {
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to delete a shelf.\n" << std::endl;
		return;
	}
	activeUser->deleteShelf(shelfName);
}

void GoodReads::addToShelf(const std::string& bookName, const std::string& shelfName) {
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to add a book to a shelf.\n" << std::endl;
		return;
	}
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i]->getTitle() == bookName) {
			book = books[i];
			break;
		}
	}
	if (book == nullptr) {
		std::cout << "Book not found in the repository.\n" << std::endl;
		return;
	}
	activeUser->addToShelf(book, shelfName);
}

void GoodReads::removeFromShelf(const std::string& bookName, const std::string& shalfName) {
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to add a book to a shelf.\n" << std::endl;
		return;
	}
	activeUser->removeFromShelf(bookName, shalfName);
}

void GoodReads::deleteBook(const std::string& bookName) {
	activeUser->deleteBook(bookName);
}

void GoodReads::showShelf(const std::string& username, const std::string& shelfName) const  {
	if (username == "") {
		activeUser->showShelf(shelfName);
		return;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			users[i]->showShelf(shelfName);
			return;
		}
	}
	std::cout << "User not found.\n" << std::endl;
}

void GoodReads::showInbox(const std::string& filter) const  {
	activeUser->showInbox(filter);
	std::cout << std::endl;
}

void GoodReads::readMessage(const int index) {
	activeUser->readMessage(index);
}

void GoodReads::deleteMessage(const int index) {
	activeUser->deleteMessage(index);
}

void GoodReads::friends(const std::string& username) const {
	if (username == "") {
		activeUser->printFriends();
		return;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			users[i]->printFriends();
			return;
		}
	}
	std::cout << "User not found.\n" << std::endl;
}

void GoodReads::addBirthday(const Date& birthday) {
	activeUser->setBirthday(birthday);
}

void GoodReads::profile(const std::string& username) const {
	std::shared_ptr<User> user = nullptr;
	if (username == "") {
		user = activeUser;
	}
	else {
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == username) {
				user = users[i];
				break;
			}
		}
		if (user == nullptr) {
			std::cout << "User not found\n";
			return;
		}
	}
	std::cout << "Username: " << user->getUsername() << std::endl;
	std::cout << "Birthday: ";
	user->getBirthday().printDate();
	std::cout << std::endl;
	std::cout << "Shelves:\n";
	user->printShelves();
	std::cout << std::endl;
	std::cout << "Favorite Books:\n";
	user->printFavoriteBooks();
	std::cout << std::endl;
	std::cout << "Registered on: ";
	user->getRegistrationDate().printDate();
	std::cout << std::endl;
}

void GoodReads::acceptOffer(const int index) const {
	std::string publisherName = activeUser->getPublisher(index);
	if (publisherName != "") {
		std::shared_ptr<User> publisher = nullptr;
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == publisherName) {
				publisher = users[i];
			}
		}
		activeUser->acceptOffer(index, publisher);
		publisher->workWith(activeUser);
	}
	
}

void GoodReads::leave(const std::string publisherName) {
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == publisherName) {
			if (users[i]->getUserType() != "Publisher") {
				std::cout << "This user is not a publisher.\n" << std::endl;
				return;
			}
			users[i]->leave(activeUser);
			activeUser->leave(users[i]);
			return;
		}
	}
	std::cout << "Publisher not found.\n" << std::endl;
}

void GoodReads::followers() const {
	activeUser->printFollowers();
}

void GoodReads::publish(const std::string title, const std::string authorName, const Date releaseDate, const int pageCount, const std::vector<std::string> genres) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i]->getTitle() == title) {
			std::cout << "A book with this title already exists.\n" << std::endl;
			return;
		}
	}
	std::shared_ptr<User> author = nullptr;
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == authorName) {
			author = users[i];
			break;
		}
	}
	if (author == nullptr) {
		std::cout << "Invalid author.\n" << std::endl;
		return;
	}
	std::shared_ptr<Book> newBook = std::make_shared<Book>(title, authorName, activeUser->getUsername(), releaseDate, pageCount, genres);
	books.push_back(newBook);
	std::cout << "You have successfully published the book " << title << "\n" << std::endl;
	std::string activeUserUsername = activeUser->getUsername();
	std::string messageContent = "";
	for (size_t i = 0; i < users.size(); i++) {
		if (author->isFollowedBy(users[i]->getUsername()) && activeUser->isFollowedBy(users[i]->getUsername())) {
			messageContent = "New book published by author " + authorName + " and publisher " + activeUser->getUsername() + ": " + title;
		}
		else if (author->isFollowedBy(users[i]->getUsername())) {
			messageContent = "New book published by author " + authorName + ": " + title;
		}
		else if (activeUser->isFollowedBy(users[i]->getUsername())) {
			messageContent = "New book published by publisher" + activeUser->getUsername() + ": " + title;
		}
		std::shared_ptr<Message> message = std::make_shared<Message>(activeUserUsername, 0, messageContent);
		users[i]->receiveMessage(message);
	}
	activeUser->publish(newBook);
}

void GoodReads::addSynopsis(const std::string bookTitle, const std::string synopsis) {
	for (size_t i = 0; i < books.size(); i++) {
		if (books[i]->getTitle() == bookTitle) {
			if (books[i]->getSynopsis() != "") {
				std::cout << "This book already has a synopsis.\n" << std::endl;
				return;
			}
			books[i]->addSynopsis(synopsis);
			std::cout << "You have successfully added a synopsis to " << bookTitle << ".\n" << std::endl;
			return;
		}
	}
	std::cout << "Book not found.\n" << std::endl;
}

void GoodReads::offer(const std::string authorName) {
	if (activeUser->getUsername() == authorName) {
		std::cout << "You cannot send yourself a job offer.\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == authorName) {
			if (users[i]->getUserType() != "Author") {
				std::cout << "This user is not an author, you cannot send them a job offer.\n" << std::endl;
				return;
			}
			if (users[i]->hasSentJobOffer(activeUser)) {
				std::cout << "This author already has a job offer from you.\n" << std::endl;
				return;
			}
			if (activeUser->isWorkingWithAuthor(users[i])) {
				std::cout << "You are already working with this author.\n" << std::endl;
				return;
			}
			if (users[i]->getUsername() == authorName && users[i]->getUserType() == "Author") {
				std::string activeUserUsername = activeUser->getUsername();
				std::string messageContent = activeUserUsername + " has sent you a job offer.";
				std::shared_ptr<Message> message = std::make_shared<Message>(activeUserUsername, 0, messageContent);
				users[i]->receiveMessage(message);
				std::cout << "You have sent " << authorName <<" a job offer.\n" << std::endl;
				return;
			}
		}
	}
	std::cout << "Author not found.\n" << std::endl;
}

// just for testing
void GoodReads::addBook(const std::shared_ptr<Book> book) {
	books.push_back(book);
}