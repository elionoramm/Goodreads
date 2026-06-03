#pragma once
#include <iostream>
#include <memory>
#include "GoodReads.h"
#include "User.h"
#include "Reader.h"
#include "Author.h"
#include "Publisher.h"
#include "UsernameValidator.h"
#include "PasswordValidator.h"
#include "UserValidators.h"

class UserFactory {
public:
	static std::shared_ptr<User> createUser(const std::string& userType, const std::string& username, const std::string& password);
};