#include "RegisterCommand.h"

Register::Register(GoodReads& goodReads) : goodReads(goodReads) {}

void Register::execute(std::vector<std::string> params) {
	if (params.size() != 3) {
		throw WrongCommandUsage("Usage: register <username> <password> <userType>\n");
	}
	UserSystem& userSystem = goodReads.getUserSystem();
	std::shared_ptr<User> activeUser = goodReads.getActiveUser();
	std::string username = params[0];
	std::string password = params[1];
	std::string userType = params[2];
	try {
		std::shared_ptr<User> user = UserFactory::createUser(userType, username, password);
		userSystem.addUser(user);
		std::cout << "User registered successfully.\n" << std::endl;
		goodReads.setActiveUser(user);
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