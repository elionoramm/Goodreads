#include "GoodReads.h"

GoodReads::GoodReads(){
	bookSystem = BookSystem();
	auto userValidationService = std::make_unique<UserValidationService>();
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
	
	userValidationService->addValidator(usernameValidator);
	userValidationService->addValidator(passwordValidator);
	userSystem = UserSystem(*userValidationService);
	activeUser = nullptr;
	std::fstream file;
	file.open("GoodReads.txt", std::fstream::in);
	if (file.is_open()) {
		bookSystem.loadBookSystem(file);
		userSystem.loadUserSystem(file, bookSystem);
	}
	else {
		std::cout << "No save file found." << std::endl;
	}
}

UserSystem& GoodReads::getUserSystem() {
	return userSystem;
}

BookSystem& GoodReads::getBookSystem() {
	return bookSystem;
}

std::shared_ptr<User> GoodReads::findUser(const std::string& username) const {
	return userSystem.findUser(username);
}

std::shared_ptr<Book> GoodReads::findBook(const std::string& bookName) const {
	return bookSystem.findBook(bookName);
}

std::shared_ptr<User> GoodReads::getActiveUser() const {
	return activeUser;
}

std::shared_ptr<Reader> GoodReads::getActiveReader() const {
	if (activeUser == nullptr) {
		return nullptr;
	}
	else if (activeUser->getUserType() != "publisher") {
		return dynamic_pointer_cast<Reader>(activeUser);
	}
	throw WrongUserCommand("publisher");
	return nullptr;
}

std::shared_ptr<Author> GoodReads::getActiveAuthor() const {
	if (activeUser == nullptr) {
		return nullptr;
	}
	else if (activeUser->getUserType() == "author") {
		return dynamic_pointer_cast<Author>(activeUser);
	}
	throw WrongUserCommand(activeUser->getUserType());
	return nullptr;
}

std::shared_ptr<Publisher> GoodReads::getActivePublisher() const {
	if (activeUser == nullptr) {
		return nullptr;
	}
	else if (activeUser->getUserType() == "publisher") {
		return dynamic_pointer_cast<Publisher>(activeUser);
	}
	throw WrongUserCommand(activeUser->getUserType());
	return nullptr;
}

std::shared_ptr<Reader> GoodReads::toReader(const std::shared_ptr<User> user) const {
	if (user->getUserType() != "publisher") {
		return dynamic_pointer_cast<Reader>(user);
	}
	throw std::invalid_argument(user->getUserType() + " is not a reader.\n");
	return nullptr;
}

std::shared_ptr<Author> GoodReads::toAuthor(const std::shared_ptr<User> user) const {
	if (user->getUserType() == "author") {
		return dynamic_pointer_cast<Author>(user);
	}
	throw std::invalid_argument(user->getUserType() + " is not a author.\n");
	return nullptr;
}

std::shared_ptr<Publisher> GoodReads::toPublisher(const std::shared_ptr<User> user) const {
	if (user->getUserType() == "publisher") {
		return dynamic_pointer_cast<Publisher>(user);
	}
	throw std::invalid_argument(user->getUserType() + " is not a publisher.\n");
	return nullptr;
}