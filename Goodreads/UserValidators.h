#pragma once
#include <vector>
#include <memory>
#include "UserValidator.h"

class UserValidators{
private:
	std::vector<std::unique_ptr<UserValidator>> validators;
	void copyFrom(const UserValidators& other);
public:
	UserValidators() = default;
	UserValidators(const UserValidators& other);
	UserValidators& operator=(const UserValidators& other);
	UserValidators(UserValidators&&) = default;
	UserValidators& operator=(UserValidators&&) = default;
	void addValidator(const UserValidator& validator);
	std::vector<std::string> validate(const std::shared_ptr<User>& user) const;
};