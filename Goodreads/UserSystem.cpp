#include "UserSystem.h"

UserSystem::UserSystem(const UserValidators& userValidators) : userValidators(userValidators) {}

const std::vector<std::shared_ptr<User>>& UserSystem::getUsers() const {
    return users;
}

std::optional<std::shared_ptr<User>> UserSystem::operator[](const std::string& username) const {
    auto it = std::ranges::find_if(users, [&username](const std::shared_ptr<User>& user) {
        return user->getUsername() == username;
        });
    if (it == users.end()) {
        return std::nullopt;
    }
    return *it;
}

void UserSystem::addUser(const std::shared_ptr<User>& user) {
    if (this->operator[](user->getUsername()).has_value()) {
        throw UserAlreadyExistsException(std::format("User with username {} already exists.", user->getUsername()));
    }
    std::vector<std::string> errors = userValidators.validate(user);
    if (!errors.empty()) {
        throw ValidationFailedException("User validation failed!", errors);
    }
    users.push_back(user);
}