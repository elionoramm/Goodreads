#include "GoodReads.h"

GoodReads::GoodReads() {
	activeUser = nullptr;
	std::fstream file;
	file.open("GoodReads.txt", std::fstream::in);
	if (file.is_open()) {
		std::string usersCount;
		file >> usersCount;
		for (size_t i = 0; i < static_cast<size_t>(std::stoull(usersCount)); i++) {
			std::string userType, username, password;
			file >> userType >> username >> password;
			try {
				users.push_back(UserFactory::createUser(userType, username, password));
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what() << "\n" << std::endl;
			}
			users[i]->loadUser(file);
		}
	}
	else {
		std::cout << "No save file found." << std::endl;
	}
}

void GoodReads::help(const std::vector<std::string>& params) const {
	if (params.size() != 0) {
		std::cout << "Usage: help\n" << std::endl;
		return;
	}
	if (activeUser == nullptr) {
		std::cout << "No user is currently logged in. Use either \n"
			"register <username> <password> <userType>\n"
			"login <username> <password>\n" << std::endl;
		return;
	}
	activeUser->help();
	std::cout << std::endl;
}

void GoodReads::registerUser(const std::vector<std::string>& params) {
	if (params.size() != 3) {
		std::cout << "Usage: register <username> <password> <userType>\n" << std::endl;
		return;
	}
	std::string username = params[0];
	std::string password = params[1];
	std::string userType = params[2];
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			std::cout << "Username already exists.\n" << std::endl;
			return;
		}
	}
	try {
		users.push_back(UserFactory::createUser(userType, username, password));
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << "\n" << std::endl;
		return;
	}
	std::cout << "User registered successfully.\n";
	logIn({ username, password });
}

void GoodReads::logIn(const std::vector<std::string>& params) {
	if (params.size() != 2) {
		std::cout << "Usage: login <username> <password>\n" << std::endl;
		return;
	}
	std::string username = params[0];
	std::string password = params[1];
	if (activeUser != nullptr) {
		logOut({});
	}
	else if (activeUser != nullptr && activeUser->getUsername() == username) {
		std::cout << "You are already logged in.\n" << std::endl;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			if (users[i]->getPassword() == password) {
				activeUser = users[i];
				std::cout << "Logged in successfully.\n" << std::endl;
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

void GoodReads::logOut(const std::vector<std::string>& params) {
	if (params.size() != 0) {
		std::cout << "Usage: logout\n" << std::endl;
		return;
	}
	if (activeUser == nullptr) {
		std::cout << "No user is currently logged in.\n" << std::endl;
		return;
	}
	activeUser = nullptr;
	std::cout << "Logged out successfully.\n" << std::endl;
}

void GoodReads::exit(const std::vector<std::string>& params) {
	if (params.size() != 0) {
		std::cout << "Usage: exit\n" << std::endl;
		return;
	}
	std::fstream file;
	file.open("GoodReads.txt", std::fstream::out);
	if (file.is_open()) {
		file << users.size() << std::endl;
		for (size_t i = 0; i < users.size(); i++) {
			users[i]->saveUser(file);
		}
		file.close();
	}
	std::cout << "Exiting the application. Goodbye.\n" << std::endl;
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

void GoodReads::search(const std::vector<std::string>& params) const {
	if (params.size() != 1) {
		std::cout << "Usage: search <name>\n" << std::endl;
		return;
	}
	std::string name = params[0];
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
	std::vector<std::shared_ptr<Book>> books;
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUserType() == "publisher") {
			books = users[i]->getBooks();
			for (size_t j = 0; j < books.size(); j++) {
				if (books.size() != 0 && caseInsensitiveMatch(books[j]->getTitle(), name)) {
					std::cout << books[j]->getTitle() << " (" << books[j]->getAverageRating() << ")" << std::endl;
					matches++;
				}
			}
		}
	}
	if (matches == 0) {
		std::cout << "No matches found.\n";
	}
	std::cout << std::endl;
}

void GoodReads::follow(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: search <name>\n" << std::endl;
		return;
	}
	std::string username = params[0];
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to follow someone.\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			users[i]->addFollower(activeUser->getUsername());
			return;
		}
	}
	std::cout << "Username not found.\n" << std::endl;
}

void GoodReads::addToCollection(const std::vector<std::string>& params) {
	if (params.size() != 2 && params.size() != 3) {
		std::cout << "Usage: add-book <bookName> <status> <rating>*\n" << std::endl;
		return;
	}
	double rating = 0.0;
	if (params.size() == 3 && params[2] != "") {
		for (size_t i = 0; i < params[2].size(); i++) {
			if ((params[2][i] > '9' || params[2][i] < '0') && params[2][i] != '.') {
				std::cout << "Invalid ratung.\n" << std::endl;
				return;
			}
		}
		rating = std::stod(params[2]);
	}
	std::string bookName = params[0];
	std::string status = params[1];
	if (status != "want-to-read" && status != "currently-reading" && status != "paused" && status != "did-not-finish" && status != "read") {
		std::cout << "Invalid status.\n" << std::endl;
		return;
	}
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to add a book.\n" << std::endl;
		return;
	}
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUserType() == "publisher") {
			book = users[i]->getBookByTitle(bookName);
			if (book != nullptr) {
				break;
			}
		}
	}
	if (book == nullptr) {
		std::cout << "Book not found in the system.\n" << std::endl;
		return;
	}
	activeUser->addToCollection(book, status, rating);
}

void GoodReads::createShelf(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: create-shelf <name>\n" << std::endl;
		return;
	}
	std::string shelfName = params[0];
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to create a shelf.\n" << std::endl;
		return;
	}
	activeUser->createShelf(shelfName);
}

void GoodReads::deleteShelf(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: delete-shelf <name>\n" << std::endl;
		return;
	}
	std::string shelfName = params[0];
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to delete a shelf.\n" << std::endl;
		return;
	}
	activeUser->deleteShelf(shelfName);
}

void GoodReads::addToShelf(const std::vector<std::string>& params) {
	if (params.size() != 2) {
		std::cout << "Usage: add-to-shelf <bookName> <shelfName>\n" << std::endl;
		return;
	}
	std::string bookName = params[0];
	std::string shelfName = params[1];
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to add a book to a shelf.\n" << std::endl;
		return;
	}
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUserType() == "publisher") {
			book = users[i]->getBookByTitle(bookName);
			if (book != nullptr) {
				break;
			}
		}
	}
	if (book == nullptr) {
		std::cout << "Book not found in the system.\n" << std::endl;
		return;
	}
	activeUser->addToShelf(book, shelfName);
}

void GoodReads::removeFromShelf(const std::vector<std::string>& params) {
	if (params.size() != 2) {
		std::cout << "Usage: remove-from-shelf <bookName> <shelfName>\n" << std::endl;
		return;
	}
	std::string bookName = params[0];
	std::string shelfName = params[1];
	if (activeUser == nullptr) {
		std::cout << "You must be logged into an account to add a book to a shelf.\n" << std::endl;
		return;
	}
	activeUser->removeFromShelf(bookName, shelfName);
}

void GoodReads::deleteBook(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: delete-book <bookName>\n" << std::endl;
		return;
	}
	std::string bookName = params[0];
	activeUser->deleteBook(bookName);
}

void GoodReads::showShelf(const std::vector<std::string>& params) const  {
	if (params.size() != 1 && params.size() != 2) {
		std::cout << "Usage: show-shelf <reader>* <shelfName>\n" << std::endl;
		return;
	}
	std::string username = "";
	std::string shelfName;
	if (params.size() == 2) {
		username = params[0];
		shelfName = params[1];
	}
	else if (params.size() == 1) {
		shelfName = params[0];
	}
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

void GoodReads::showInbox(const std::vector<std::string>& params) const  {
	if (params.size() != 0 && params.size() != 1) {
		std::cout << "Usage: show-inbox <filter>*\n" << std::endl;
		return;
	}
	std::string filter = "";
	if (params.size() == 1) {
		filter = params[0];
	}
	activeUser->showInbox(filter);
	std::cout << std::endl;
}

void GoodReads::readMessage(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: read-msg <index>\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < params[0].size(); i++) {
		if (params[0][i] > '9' || params[0][i] < '0') {
			std::cout << "Invalid index.\n" << std::endl;
			return;
		}
	}
	int index = std::stoi(params[0]);
	activeUser->readMessage(index);
}

void GoodReads::deleteMessage(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: delete-msg <index>\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < params[0].size(); i++) {
		if (params[0][i] > '9' || params[0][i] < '0') {
			std::cout << "Invalid index.\n" << std::endl;
			return;
		}
	}
	int index = std::stoi(params[0]);
	activeUser->deleteMessage(index);
}

void GoodReads::friends(const std::vector<std::string>& params) const {
	if (params.size() != 0 && params.size() != 1) {
		std::cout << "Usage: friends <reader>*\n" << std::endl;
		return;
	}
	std::string username = "";
	if (params.size() == 1) {
		username = params[0];
	}
	std::shared_ptr<User> user = nullptr;
	int friendCount = 0;
	if (username == "") {
		user = activeUser;
	}
	else {
		for (size_t i = 0; i < users.size(); i++) {
			if (user == nullptr && users[i]->getUsername() == username) {
				user = users[i];
			}
		}
		if (user == nullptr) {
			std::cout << "User not found.\n" << std::endl;
			return;
		}
	}
	std::cout << "Friends:\n";
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->isFollowedBy(user->getUsername()) && user->isFollowedBy(users[i]->getUsername())) {
			std::cout << "- " << users[i]->getUsername() << std::endl;
			friendCount++;
		}
	}
	if (friendCount == 0) {
		std::cout << "This user has no friends yet.\n";
	}
	std::cout << std::endl;
}

void GoodReads::addBirthday(const std::vector<std::string>& params) {
	if (params.size() != 0 && params.size() != 1) {
		std::cout << "Usage: add-birthday <date>*\n" << std::endl;
		return;
	}
	Date birthday;
	if (params.size() == 0) {
		birthday = Date();
	}
	else if (params.size() == 1) {
		for (size_t i = 0; i < params[0].size(); i++) {
			if ((params[0][i] > '9' || params[0][i] < '0') && params[0][i] != '/') {
				std::cout << "Invalid date, format: day/mont/year.\n" << std::endl;
				return;
			}
		}
		birthday = Date(params[0]);
	}
	activeUser->setBirthday(birthday);
}

void GoodReads::profile(const std::vector<std::string>& params) const {
	if (params.size() != 0 && params.size() != 1) {
		std::cout << "Usage: profile <reader>*\n" << std::endl;
		return;
	}
	std::string username;
	if (params.size() == 0) {
		username = "";
	}
	else {
		username = params[0];
	}
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

void GoodReads::acceptOffer(const std::vector<std::string>& params) const {
	if (params.size() != 1) {
		std::cout << "Usage: accept-offer <index>\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < params[0].size(); i++) {
		if (params[0][i] > '9' || params[0][i] < '0') {
			std::cout << "Invalid index.\n" << std::endl;
			return;
		}
	}
	int index = std::stoi(params[0]);
	std::string publisherName = activeUser->getPublisher(index);
	if (publisherName != "") {
		std::shared_ptr<User> publisher = nullptr;
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == publisherName) {
				publisher = users[i];
			}
		}
		activeUser->acceptOffer(index, publisherName);
		publisher->workWith(activeUser->getUsername());
		return;
	}
}

void GoodReads::leave(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: leave <publisher>\n" << std::endl;
		return;
	}
	std::string publisherName = params[0];
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == publisherName) {
			if (users[i]->getUserType() != "publisher") {
				std::cout << "This user is not a publisher.\n" << std::endl;
				return;
			}
			users[i]->leave(activeUser->getUsername());
			activeUser->leave(users[i]->getUsername());
			return;
		}
	}
	std::cout << "Publisher not found.\n" << std::endl;
}

void GoodReads::followers(const std::vector<std::string>& params) const {
	if (params.size() != 0) {
		std::cout << "Usage: followers\n" << std::endl;
		return;
	}
	activeUser->printFollowers();
}

void GoodReads::publish(const std::vector<std::string>& params) {
	if (params.size() < 5) {
		std::cout << "Usage: publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres>\n" << std::endl;
		return;
	}
	std::string bookName = params[0];
	std::string authorName = params[1];
	for (size_t i = 0; i < params[2].size(); i++) {
		if ((params[2][i] > '9' || params[2][i] < '0') && params[2][i] != '/') {
			std::cout << "Invalid date, format: day/mont/year.\n" << std::endl;
			return;
		}
	}
	Date releaseDate = Date(params[2]);
	for (size_t i = 0; i < params[3].size(); i++) {
		if (params[3][i] > '9' || params[3][i] < '0') {
			std::cout << "Invalid page count.\n" << std::endl;
			return;
		}
	}
	int pageCount = std::stoi(params[3]);
	std::vector<std::string> genres;
	for (int i = 4; i < params.size(); i++) {
		genres.push_back(params[i]);
	}
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUserType() == "publisher") {
			book = users[i]->getBookByTitle(bookName);
			if (book != nullptr) {
				break;
			}
		}
	}
	if (book != nullptr) {
		std::cout << "Book with this title already exists.\n" << std::endl;
		return;
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
	if (!activeUser->isWorkingWithAuthor(authorName)) {
		std::cout << "You are not working with this author you cannot publish their book.\n" << std::endl;
		return;
	}
	std::shared_ptr<Book> newBook = std::make_shared<Book>(bookName, authorName, activeUser->getUsername(), releaseDate, pageCount, genres);
	std::cout << "You have successfully published the book " << bookName << "\n" << std::endl;
	std::string activeUserUsername = activeUser->getUsername();
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
		if(messageContent != "") {
			Message message = Message(activeUserUsername, 0, messageContent);
			users[i]->receiveMessage(message);
		}
	}
	activeUser->publish(newBook);
	author->publish(newBook);
}

void GoodReads::addSynopsis(const std::vector<std::string>& params) {
	if (params.size() < 2) {
		std::cout << "Usage: add-synopsis <bookTitle> <synopsis>\n" << std::endl;
		return;
	}
	std::string bookName = params[0];
	std::string synopsis = "#";
	for (size_t i = 1; i < params.size(); i++) {
		synopsis = synopsis + params[i] + " ";
	}
	std::shared_ptr<Book> book = activeUser->getBookByTitle(bookName);
	if (book == nullptr) {
		std::cout << "You cannot add a synopsis to a book that wasn't published by you.\n" << std::endl;
		return;
	}
	else if (book->getSynopsis() != "#") {
		std::cout << "This book already has a synopsis.\n" << std::endl;
		return;
	}
	book->addSynopsis(synopsis);
	std::cout << "You have successfully added a synopsis to " << bookName << ".\n" << std::endl;
}

void GoodReads::offer(const std::vector<std::string>& params) {
	if (params.size() != 1) {
		std::cout << "Usage: offer <author>\n" << std::endl;
		return;
	}
	std::string authorName = params[0];
	if (activeUser->getUsername() == authorName) {
		std::cout << "You cannot send yourself a job offer.\n" << std::endl;
		return;
	}
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == authorName) {
			if (users[i]->getUserType() != "author") {
				std::cout << "This user is not an author, you cannot send them a job offer.\n" << std::endl;
				return;
			}
			if (users[i]->hasSentJobOffer(activeUser->getUsername())) {
				std::cout << "This author already has a job offer from you.\n" << std::endl;
				return;
			}
			if (activeUser->isWorkingWithAuthor(users[i]->getUsername())) {
				std::cout << "You are already working with this author.\n" << std::endl;
				return;
			}
			if (users[i]->getUsername() == authorName && users[i]->getUserType() == "author") {
				std::string activeUserUsername = activeUser->getUsername();
				std::string messageContent = activeUserUsername + " has sent you a job offer.";
				Message message = Message(activeUserUsername, 0, messageContent);
				users[i]->receiveMessage(message);
				std::cout << "You have sent " << authorName <<" a job offer.\n" << std::endl;
				return;
			}
		}
	}
	std::cout << "Author not found.\n" << std::endl;
}