#include "UserFactory.h"

std::shared_ptr<User> UserFactory::createUser(const std::string& userType, const std::string& username, const std::string& password) {
	if (userType == "reader") {
		return std::make_shared<Reader>(username, password);
	}
	else if (userType == "author") {
		return std::make_shared<Author>(username, password);
	}
	else if (userType == "publisher") {
		return std::make_shared<Publisher>(username, password);
	}
	throw std::invalid_argument("Invalid user type: " + userType);
}