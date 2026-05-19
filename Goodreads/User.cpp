#include "User.h"

std::string User::getUsername() const {
	return username;
}

std::string User::getPassword() const {
	return password;
}

Date User::getRegistrationDate() const {
	return registrationDate;
}