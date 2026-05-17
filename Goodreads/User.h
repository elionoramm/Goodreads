#pragma once
#include "Date.h"
#include <string>
class User {
protected:
	std::string username;
	std::string password;
	Date registrationDate;
	unsigned int followers;
public:
	virtual std::string getUserType() const = 0;
	std::string getUsername() const;
	std::string getPassword() const;
};