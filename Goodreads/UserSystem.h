#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <format>
#include "User.h"
#include "UserValidators.h"
#include "CustomUserExceptions.h"

class UserSystem {
private:
    std::vector<std::shared_ptr<User>> users;
    UserValidators userValidators;
public:
	UserSystem() = default;
    UserSystem(const UserValidators& userValidators);
    const std::vector<std::shared_ptr<User>>& getUsers() const;
    std::optional<std::shared_ptr<User>> operator[](const std::string& username) const;
    void addUser(const std::shared_ptr<User>& user);
};