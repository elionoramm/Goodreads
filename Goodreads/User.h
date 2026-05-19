#pragma once
#include <string>
#include <memory>
#include "Date.h"
class User {
protected:
	std::string username;
	std::string password;
	Date registrationDate;
public:
	virtual std::string getUserType() const = 0;
	std::string getUsername() const;
	std::string getPassword() const;
	Date getRegistrationDate() const;
};