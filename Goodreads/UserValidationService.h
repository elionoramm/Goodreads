#pragma once
#include <vector>
#include <memory>
#include "UserValidator.h"

class UserValidationService {
private:
	std::vector<std::unique_ptr<UserValidator>> validators;
	void copyFrom(const UserValidationService& other);
public:
	UserValidationService() = default;
	UserValidationService(const UserValidationService& other);
	UserValidationService& operator=(const UserValidationService& other);
	UserValidationService(UserValidationService&&) = default;
	UserValidationService& operator=(UserValidationService&&) = default;
	void addValidator(const UserValidator& validator);
	std::vector<std::string> validate(const std::shared_ptr<User>& user) const;
};