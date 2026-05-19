#include "Commands.h"
#include "Repository.cpp"

// Implementing the Help command
void Help::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1) {
		std::cout << "Usage: help\n" << std::endl;
		return;
	}
	if(GoodReads::instance->getActiveUser() == nullptr) {
		std::cout << "No user is currently logged in.\n" << std::endl;
		return;
	}
	auto activeUser = GoodReads::instance->getActiveUser();
	std::string userType = activeUser->getUserType();
	std::cout << "register <username> <password> <userType>\n"
		"login <username> <password>\n"
		"logout\n"
		"exit\n";
	if (userType == "Reader" || userType == "Author") {
		std::cout << "search <name>\n"
			"follow <username>\n"
			"add_book <bookName> <status> <rating>*\n"
			"create_shelf <name>\n"
			"delete_shelf <name>\n"
			"add_to_shelf <bookName> <shelfName>\n"
			"remove_from_shelf <bookName> <shelfName>\n"
			"delete_book <bookName>\n"
			"show_shelf <reader>* <shelfName>\n"
			"show_inbox <filter>*\n"
			"read_msg <index>\n"
			"delete_msg <index>\n"
			"friends <reader>*\n"
			"add_birthday <date>*\n"
			"profile <reader>*\n";
	}
	if (userType == "Author") {
		std::cout << "accept_offer <index>\n"
			"leave <publisher>\n"
			"followers\n";
	}
	if (userType == "Publisher") {
		std::cout << "publish <book_title>\n"
			"add_synopsis <book_title> <synopsis>\n"
			"offer <author_username> <book_title> <synopsis>\n" << std::endl;
	}
}

// Implementing the Register command
void Register::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 4) {
		std::cout << "Usage: register <username> <password> <userType>\n" << std::endl;
		return;
	}
	else {
		std::string username = substrings[1];
		std::string password = substrings[2];
		std::string userType = substrings[3];
		Repository<User> users = GoodReads::instance->getUsers();
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == username) {
				std::cout << "Username already exists.\n" << std::endl;
				return;
			}
		}
		std::shared_ptr<User> newUser;
		if (userType == "reader") {
			newUser = std::make_shared<Reader>(username, password);
		}
		else if (userType == "author") {
			newUser = std::make_shared<Author>(username, password);
		}
		else if (userType == "publisher") {
			newUser = std::make_shared<Publisher>(username, password);
		}
		else {
			std::cout << "Invalid user type. Must be 'reader', 'author', or 'publisher'.\n" << std::endl;
			return;
		}
		GoodReads::instance->getUsers().addElement(newUser);
		std::cout << "User registered successfully!\n" << std::endl;
		GoodReads::instance->setActiveUser(newUser);
		std::cout << "You are now logged in as " << username << ".\n" << std::endl;
	}
}

// Implementing the Login command
void Login::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		std::cout << "Usage: login <username> <password>\n" << std::endl;
		return;
	}
	std::string username = substrings[1];
	std::string password = substrings[2];
	Repository<User> users = GoodReads::instance->getUsers();
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			if (users[i]->getPassword() == password) {
				GoodReads::instance->setActiveUser(users[i]);
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

// Implementing the Logout command
void Logout::execute(std::vector<std::string> substrings) {
	if (GoodReads::instance->getActiveUser() == nullptr) {
		std::cout << "No user is currently logged in.\n" << std::endl;
		return;
	}
	GoodReads::instance->setActiveUser(nullptr);
	std::cout << "Logged out successfully.\n" << std::endl;
}

// Implementing the Exit command
void Exit::execute(std::vector<std::string> substrings) {
	std::cout << "Exiting the application. Goodbye!" << std::endl;
	exit(0);
}

// Implementing the Search command
bool Search::caseInsensitiveMatch(const std::string& str1, const std::string& str2) {
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

void Search::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: search <name>\n" << std::endl;
		return;
	}
	std::string name = substrings[1];
	Repository<User>& users = GoodReads::instance->getUsers();
	Repository<Book>& books = GoodReads::instance->getBooks();
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

// Implementing the Follow command
void Follow::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: search <name>\n" << std::endl;
		return;
	}
	std::string username = substrings[1];
	Repository<User>& users = GoodReads::instance->getUsers();
	std::shared_ptr<Reader> reader = nullptr;
	for (size_t i = 0; i < users.size(); i++) {
		if (users[i]->getUsername() == username) {
			if (users[i] == GoodReads::instance->getActiveUser()) {
				std::cout << "You cannot follow yourself.\n" << std::endl;
				return;
			}
			reader = std::dynamic_pointer_cast<Reader>(users[i]);
		}
	}
	if (reader == nullptr) {
		std::cout << "Username not found.\n" << std::endl;
		return;
	}
	reader->getFollowers().addElement(GoodReads::instance->getActiveUser());
	std::cout << "You are now following " << username << ".\n" << std::endl;
	std::string activeUserUsername = GoodReads::instance->getActiveUser()->getUsername();
	std::string messageContent = activeUserUsername + " has sent you a friend request.";
	std::shared_ptr<Message> message = std::make_shared<Message>(activeUserUsername, 0, messageContent);
	reader->receiveMessage(message);
}
// WIP what do we do about the status
// Implementing the AddBook command
void AddBook::execute(std::vector<std::string> substrings) {
	std::string bookName;
	std::string status;
	double rating = 0;
	if (substrings.size() == 4) {
		bookName = substrings[1];
		status = substrings[2];
		rating = std::stod(substrings[3]);
	}
	else if (substrings.size() == 3) {
		bookName = substrings[1];
		status = substrings[2];
	}
	else {
		std::cout << "Usage: add_book <bookName> <status> <rating>*\n" << std::endl;
		return;
	}
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	std::shared_ptr<Book> book = nullptr;
	Repository<Book>& existingBooks = GoodReads::instance->getBooks();
	Repository<Book>& userBooks = reader->getBooks();
	for (size_t i = 0; i < userBooks.size(); i++) {
		if (userBooks[i]->getTitle() == bookName) {
			std::cout << "Book already exists in your collection.\n" << std::endl;
			return;
		}
	}
	for (size_t i = 0; i < existingBooks.size(); i++) {
		if (existingBooks[i]->getTitle() == bookName) {
			book = existingBooks[i];
			break;
		}
	}
	if (book == nullptr) {
		std::cout << "Book not found in the repository.\n" << std::endl;
		return;
	}
	reader->addBook(book, status, rating);
	std::cout << "Book '" << bookName << "' added to your collection with status '" << status << "'\n" << std::endl;
}

// Implementing the CreateShelf command
void CreateShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: crate-shelf <name>\n" << std::endl;
		return;
	}
	std::string shelfName = substrings[1];
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	Repository<Shelf>& shelves = reader->getShelves();
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			std::cout << "A shelf with this name already exists.\n" << std::endl;
			return;
		}
	}
	reader->createShelf(shelfName);
	std::cout << "Shelf '" << shelfName << "' created successfully.\n" << std::endl;
}

// Implementing the DeleteShelf command
void DeleteShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: delete-shelf <name>\n" << std::endl;
		return;
	}
	std::string shelfName = substrings[1];
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	Repository<Shelf>& shelves = reader->getShelves();
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			shelves.removeElement(i);
			std::cout << "Shelf '" << shelfName << "' deleted successfully.\n" << std::endl;
			std::cout << reader->getShelves().size() << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

// Implementing the AddToShelf command
void AddToShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		std::cout << "Usage: add_to_shelf <bookName> <shelfName>\n" << std::endl;
		return;
	}
	std::string bookName = substrings[1];
	std::string shelfName = substrings[2];
	Repository<Book>& existingBooks = GoodReads::instance->getBooks();
	std::shared_ptr<Book> book = nullptr;
	for (size_t i = 0; i < existingBooks.size(); i++) {
		if (existingBooks[i]->getTitle() == bookName) {
			book = existingBooks[i];
			break;
		}
	}
	if (book == nullptr) {
		std::cout << "Book not found.\n" << std::endl;
		return;
	}
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	Repository<Shelf>& shelves = reader->getShelves();
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			std::vector<std::weak_ptr<Book>>& shelfBooks = reader->getShelfBooks(shelfName);
			for (size_t j = 0; j < shelfBooks.size(); j++) {
				if (shelfBooks[j].lock()->getTitle() == bookName) {
					std::cout << "Book is already on that shelf.\n" << std::endl;
					return;
				}
			}
			shelfBooks.push_back(book);
			std::cout << "Book '" << bookName << "' added to shelf '" << shelfName << "'.\n" << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

// Implementing the RemoveFromShelf command
void RemoveFromShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 3) {
		std::cout << "Usage: remove_from_shelf <bookName> <shelfName>\n" << std::endl;
		return;
	}
	std::string bookName = substrings[1];
	std::string shelfName = substrings[2];
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	Repository<Shelf>& shelves = reader->getShelves();
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			std::vector<std::weak_ptr<Book>>& shelfBooks = reader->getShelfBooks(shelfName);
			for (size_t j = 0; j < shelfBooks.size(); j++) {
				if (shelfBooks[j].lock()->getTitle() == bookName) {
					shelfBooks.erase(shelfBooks.begin() + j);
					std::cout << "Book '" << bookName << "' removed from shelf '" << shelfName << "'.\n" << std::endl;
					return;
				}
			}
			std::cout << "Book not found on that shelf.\n" << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

// Implementing the DeleteBook command
void DeleteBook::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: delete_book <bookName>\n" << std::endl;
		return;
	}
	std::string bookName = substrings[1];
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	Repository<Book>& userBooks = reader->getBooks();
	for (size_t i = 0; i < userBooks.size(); i++) {
		if (userBooks[i]->getTitle() == bookName) {
			userBooks.removeElement(i);
			std::cout << "Book '" << bookName << "' removed from your collection.\n" << std::endl;
			return;
		}
	}
	std::cout << "Book '" << bookName << "' not found in your collection.\n" << std::endl;
}

// Implementing the ShowShelf command
void ShowShelf::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2 && substrings.size() != 3) {
		std::cout << "Usage: show_shelf <reader>* <shelfName>\n" << std::endl;
		return;
	}
	std::shared_ptr<Reader> reader = nullptr;
	std::string shelfName;
	if (substrings.size() == 3) {
		std::string user = substrings[1];
		Repository<User>& users = GoodReads::instance->getUsers();
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == user) {
				reader = std::dynamic_pointer_cast<Reader>(users[i]);
			}
		}
		if (reader == nullptr) {
			std::cout << user << " not found.\n" << std::endl;
			return;
		}
		shelfName = substrings[2];
	}
	else {
		reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
		shelfName = substrings[1];
	}
	Repository<Shelf>& shelves = reader->getShelves();
	for (size_t i = 0; i < shelves.size(); i++) {
		if (shelves[i]->getName() == shelfName) {
			std::cout << "Books in shelf '" << shelfName << "':\n";
			shelves[i]->printShelf();
			std::cout << std::endl;
			return;
		}
	}
	std::cout << "Shelf not found.\n" << std::endl;
}

// Implementing the ShowInbox command
void ShowInbox::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		std::cout << "Usage: show_inbox <filter>*\n" << std::endl;
		return;
	}
	std::string filter = "";
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	if (substrings.size() == 2) {
		filter = substrings[1];
		std::cout << "Friend requests in your inbox:\n";
	}
	std::cout << "Messages in your inbox:\n";
	reader->showInbox(filter);
	std::cout << std::endl;
}

// Implementing the ReadMSG command
void ReadMSG::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: read_msg <index>\n" << std::endl;
		return;
	}
	int index = std::stoi(substrings[1]);
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	reader->readMessage(index);
	std::cout << std::endl;
}

// Implementing the DeleteMSG command
void DeleteMSG::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: delete_msg <index>\n" << std::endl;
		return;
	}
	int index = std::stoi(substrings[1]);
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	reader->deleteMessage(index);
}

// Implementing the Friends command
void Friends::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		std::cout << "Usage: friends <reader>*\n" << std::endl;
		return;
	}
	std::shared_ptr<Reader> reader = nullptr;
	if (substrings.size() == 2) {
		std::string user = substrings[1];
		Repository<User>& users = GoodReads::instance->getUsers();
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == user) {
				reader = std::dynamic_pointer_cast<Reader>(users[i]);
			}
		}
		if (reader == nullptr) {
			std::cout << user << " not found.\n" << std::endl;
			return;
		}
	}
	else {
		reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	}
	std::cout << "List of friends:\n";
	reader->printFriends(reader);
	std::cout << std::endl;
}

// Implementing the AddBirthday command
void AddBirthday::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 2) {
		std::cout << "Usage: add_birthday <date>*\n" << std::endl;
		return;
	}
	std::shared_ptr<Reader> reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	if (substrings[1].size() == 1) {
		reader->setBirthday(Date());
		std::cout << "Birthday erased successfully.\n" << std::endl;
		return;
	}
	Date birthday = Date(substrings[1]);
	reader->setBirthday(birthday);
	std::cout << "Birthday added successfully.\n" << std::endl;
}

// Implementing the Profile command
void Profile::execute(std::vector<std::string> substrings) {
	if (substrings.size() != 1 && substrings.size() != 2) {
		std::cout << "Usage: profile <reader>*\n" << std::endl;
		return;
	}
	std::shared_ptr<Reader> reader = nullptr;
	if (substrings.size() == 2) {
		std::string user = substrings[1];
		Repository<User>& users = GoodReads::instance->getUsers();
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getUsername() == user) {
				reader = std::dynamic_pointer_cast<Reader>(users[i]);
			}
		}
		if (reader == nullptr) {
			std::cout << user << " not found.\n" << std::endl;
			return;
		}
	}
	else if (substrings.size() == 1) {
		reader = std::dynamic_pointer_cast<Reader>(GoodReads::instance->getActiveUser());
	}
	std::cout << "Username: " << reader->getUsername() << "\n";
	std::cout << "Birthday: ";
	reader->getBirthday().printDate();
	std::cout << std::endl;
	std::cout << "Shelves:\n";
	reader->printShelves();
	std::cout << std::endl;
	std::cout << "Favorite Books:\n";
	reader->printFavoriteBooks();
	std::cout << std::endl;
	std::cout << "Registered on: ";
	reader->getRegistrationDate().printDate();
	std::cout << std::endl;
}