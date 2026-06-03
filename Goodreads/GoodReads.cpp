#include "GoodReads.h"

GoodReads::GoodReads(){
	auto userValidators = std::make_unique<UserValidators>();
	UsernameValidator usernameValidator = UsernameValidator::Builder()
		.minLength(6)
		.maxLength(24)
		.allowSpecialCharacters(false)
		.build();

	PasswordValidator passwordValidator = PasswordValidator::Builder()
		.minLength(12)
		.maxLength(36)
		.requireLowercaseLetter()
		.requireUppercaseLetter()
		.requireSpecialCharacter(true)
		.build();
	
	userValidators->addValidator(usernameValidator);
	userValidators->addValidator(passwordValidator);
	userSystem = UserSystem(*userValidators);
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
				std::shared_ptr<User> user = UserFactory::createUser(userType, username, password);
				user->loadUser(file);
				userSystem.addUser(user);
			}
			catch (const std::invalid_argument& ex) {
				std::cout << ex.what() << "\n" << std::endl;
			}	
		}
	}
	else {
		std::cout << "No save file found." << std::endl;
	}
	
}

std::shared_ptr<User> GoodReads::findUser(const std::string& username) const {
	std::vector<std::shared_ptr<User>> users = userSystem.getUsers();
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			return users[i];
		}
	}
	return nullptr;
}

std::shared_ptr<Book> GoodReads::findBook(const std::string& bookName) const {
	std::vector<std::shared_ptr<User>> users = userSystem.getUsers();
	for(size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUserType() == "publisher") {
			return users[i]->getBookByTitle(bookName);
		}
	}
	return nullptr;
}

std::shared_ptr<User> GoodReads::getActiveUser() const {
	return activeUser;
}

void GoodReads::help(const std::vector<std::string>& params) const {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	activeUser->help();
	std::cout << std::endl;
}

void GoodReads::registerUser(const std::vector<std::string>& params) {
	std::string username = params[0];
	std::string password = params[1];
	std::string userType = params[2];
	try {
		std::shared_ptr<User> user = UserFactory::createUser(userType, username, password);
		userSystem.addUser(user);
		std::cout << "User registered successfully.\n";
		activeUser = user;
	}
	catch (const std::invalid_argument& ex) {
		std::cout << ex.what() << '\n';
	}
	catch (const ValidationFailedException& ex) {
		std::cout << ex.what() << '\n';
		for (const std::string& error : ex.getValidationErrors()) {
			std::cout << "- " << error << '\n';
		}
		std::cout << std::endl;
	}
	catch (const UserAlreadyExistsException& ex) {
		std::cout << ex.what() << '\n';
	}
}

void GoodReads::logIn(const std::vector<std::string>& params) {
	std::string username = params[0];
	std::string password = params[1];
	if (activeUser != nullptr) {
		throw std::logic_error("You must log out before logging into a different account.\n");
	}
	if (activeUser != nullptr && activeUser->getUsername() == username) {
		throw std::logic_error("You are already logged in.\n");
	}
	std::shared_ptr<User> user = findUser(username);
	if (user == nullptr) {
		throw std::invalid_argument("Username not found.\n");
	}
	if (user->getPassword() == password) {
		activeUser = user;
		std::cout << "Logged in successfully.\n" << std::endl;
		return;
	}
	std::cout << "Incorrect password.\n" << std::endl;	
}

void GoodReads::logOut(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw std::logic_error("No user is currently logged in.");
	}
	activeUser = nullptr;
	std::cout << "Logged out successfully.\n" << std::endl;
}

void GoodReads::exit(const std::vector<std::string>& params) {
	std::fstream file;
	file.open("GoodReads.txt", std::fstream::out);
	if (file.is_open()) {
		std::vector<std::shared_ptr<User>> users = userSystem.getUsers();
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
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (activeUser->getUserType() == "publisher") {
		throw WrongUserCommand("publisher", "search");
	}
	std::string name = params[0];
	std::cout << "Users:\n";
	unsigned int matches = 0;
	std::vector<std::shared_ptr<User>> users = userSystem.getUsers();
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
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (activeUser->getUserType() == "publisher") {
		throw WrongUserCommand("publisher", "follow");
	}
	std::shared_ptr<User> user = findUser(params[0]);
	if (user == nullptr) {
		throw std::invalid_argument("Username not found.\n");
	}
	user->addFollower(activeUser->getUsername());
}

void GoodReads::addBook(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	double rating = 0.0;
	if (params.size() == 3) {
		try {
			rating = std::stod(params[2]);
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
	std::shared_ptr<Book> book = findBook(bookName);
	if (book == nullptr) {
		throw std::invalid_argument("Book not found in the system.\n");
	}
	activeUser->addBook(book, status, rating);
}

void GoodReads::createShelf(const std::vector<std::string>& params) {
	std::string shelfName = params[0];
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	activeUser->createShelf(shelfName);
}

void GoodReads::deleteShelf(const std::vector<std::string>& params) {
	std::string shelfName = params[0];
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	activeUser->deleteShelf(shelfName);
}

void GoodReads::addToShelf(const std::vector<std::string>& params) {
	std::string bookName = params[0];
	std::string shelfName = params[1];
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	std::shared_ptr<Book> book = findBook(bookName);
	if (book == nullptr) {
		throw std::invalid_argument("Book not found in the system.\n");
	}
	activeUser->addToShelf(book, shelfName);
}

void GoodReads::removeFromShelf(const std::vector<std::string>& params) {
	std::string bookName = params[0];
	std::string shelfName = params[1];
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	activeUser->removeFromShelf(bookName, shelfName);
}

void GoodReads::deleteBook(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	std::string bookName = params[0];
	activeUser->deleteBook(bookName);
}

void GoodReads::showShelf(const std::vector<std::string>& params) const  {
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
		if (activeUser == nullptr) {
			throw NotLoggedIn();
		}
		activeUser->showShelf(shelfName);
	}
	std::shared_ptr<User> user = findUser(username);
	if (user == nullptr) {
		throw std::invalid_argument("User not found.\n");
	}
	user->showShelf(shelfName);
}

void GoodReads::showInbox(const std::vector<std::string>& params) const  {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	std::string filter = "";
	if (params.size() == 1) {
		filter = params[0];
	}
	activeUser->showInbox(filter);
	std::cout << std::endl;
}

void GoodReads::readMessage(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	try {
		int index = std::stoi(params[0]);
		activeUser->readMessage(index);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid index.\n" << std::endl;
	}
}

void GoodReads::deleteMessage(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	try{
		int index = std::stoi(params[0]);
		activeUser->deleteMessage(index);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid index.\n" << std::endl;
	}
}

void GoodReads::friends(const std::vector<std::string>& params) const {
	std::shared_ptr<User> user;
	if (params.size() == 1) {
		user = findUser(params[0]);
		if (user == nullptr) {
			throw std::invalid_argument("User not found.\n");
		}
	}
	else {
		if (activeUser == nullptr) {
			throw NotLoggedIn();
		}
		user = activeUser;
	}
	if (user->getUserType() == "publisher") {
		throw WrongUserCommand("publisher", "friends");
	}
	int friendCount = 0;
	std::cout << "Friends:\n";
	std::vector<std::shared_ptr<User>> users = userSystem.getUsers();
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
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	Date birthday;
	if (params.size() == 0) {
		birthday = Date();
	}
	else if (params.size() == 1) {
		try {
			birthday = Date(params[0]);
		}
		catch (const std::out_of_range& exception) {
			std::cerr << "Invalid date: " << exception.what() << std::endl;
			throw;
		}
		catch (const std::invalid_argument& exception) {
			std::cerr << "Invalid date: " << exception.what() << std::endl;
			throw;
		}
	}
	activeUser->setBirthday(birthday);
}

void GoodReads::profile(const std::vector<std::string>& params) const {
	std::shared_ptr<User> user = nullptr;
	if (params.size() == 0) {
		if (activeUser == nullptr) {
			throw NotLoggedIn();
		}
		user = activeUser;
	}
	else {
		user = findUser(params[0]);
		if (user == nullptr) {
			throw std::invalid_argument("User not found\n");
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
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	int index;
	try {
		index = std::stoi(params[0]);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid index.\n" << std::endl;
		return;
	}
	std::string publisherName = activeUser->getPublisher(index);
	if (publisherName == "") {
		throw std::invalid_argument("Offer not found.\n");
	}
	std::shared_ptr<User> publisher = findUser(publisherName);
	if (publisher == nullptr) {
		throw std::invalid_argument("Publisher not found.\n");
	}
	activeUser->acceptOffer(index, publisherName);
	publisher->workWith(activeUser->getUsername());
}

void GoodReads::leave(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	std::string publisherName = params[0];
	if (activeUser->isWorkingWith(publisherName) != true) {
		throw std::logic_error("You are not working with this publisher.\n");
	}
	std::shared_ptr<User>user = findUser(publisherName);
	if (user == nullptr) {
		throw std::invalid_argument("Publisher not found.\n");
	}
	user->leave(activeUser->getUsername());
	activeUser->leave(user->getUsername());
}

void GoodReads::followers(const std::vector<std::string>& params) const {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (activeUser->getUserType() != "author") {
		throw WrongUserCommand(activeUser->getUserType(), "followers");
	}
	activeUser->printFollowers();
}

void GoodReads::publish(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	std::string bookName = params[0];
	std::string authorName = params[1];
	Date releaseDate;
	int pageCount;
	try {
		releaseDate = Date(params[2]);

	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid date, format: day/mont/year.\n" << std::endl;
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
	std::shared_ptr<Book> book = findBook(bookName);
	if (book != nullptr) {
		throw std::invalid_argument("Book with this title already exists.\n");
	}
	std::shared_ptr<User> author = findUser(authorName);
	if (author == nullptr) {
		throw std::invalid_argument("Invalid author.\n");
	}
	if (!activeUser->isWorkingWith(authorName)) {
		throw std::invalid_argument("You are not working with this author you cannot publish their book.\n");
	}
	std::shared_ptr<Book> newBook = std::make_shared<Book>(bookName, authorName, activeUser->getUsername(), releaseDate, pageCount, genres);
	std::cout << "You have successfully published the book " << bookName << "\n" << std::endl;
	std::string activeUserUsername = activeUser->getUsername();
	std::vector<std::shared_ptr<User>> users = userSystem.getUsers();
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
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (activeUser->getUserType() != "publisher") {
		throw WrongUserCommand(activeUser->getUserType(), "follow");
	}
	std::string bookName = params[0];
	std::string synopsis = "";
	for (size_t i = 1; i < params.size(); i++) {
		synopsis = synopsis + params[i] + " ";
	}
	std::shared_ptr<Book> book = activeUser->getBookByTitle(bookName);
	if (book == nullptr) {
		throw std::invalid_argument("You cannot add a synopsis to a book that wasn't published by you.\n");
	}
	else if (book->getSynopsis() != "") {
		throw std::logic_error("This book already has a synopsis.\n");
	}
	book->addSynopsis(synopsis);
	std::cout << "You have successfully added a synopsis to " << bookName << ".\n" << std::endl;
}

void GoodReads::offer(const std::vector<std::string>& params) {
	if (activeUser == nullptr) {
		throw NotLoggedIn();
	}
	if (activeUser->getUserType() != "publisher") {
		throw WrongUserCommand(activeUser->getUserType(), "offer");
	}
	std::string authorName = params[0];
	if (activeUser->getUsername() == authorName) {
		throw std::invalid_argument("You cannot send yourself a job offer.\n");
	}
	std::shared_ptr<User> author = findUser(authorName);
	if (author->getUserType() != "author") {
		throw std::invalid_argument("This user is not an author, you cannot send them a job offer.\n");
	}
	if (author->hasSentJobOffer(activeUser->getUsername())) {
		throw std::invalid_argument("This author already has a job offer from you.\n");
	}
	if (author == nullptr) {
		throw std::invalid_argument("Author not found.\n");
	}
	if (author->getUsername() == authorName && author->getUserType() == "author") {
		std::string activeUserUsername = activeUser->getUsername();
		std::string messageContent = activeUserUsername + " has sent you a job offer.";
		Message message = Message(activeUserUsername, 0, messageContent);
		author->receiveMessage(message);
		std::cout << "You have sent " << authorName << " a job offer.\n" << std::endl;
	}
}