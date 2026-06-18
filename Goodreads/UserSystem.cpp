#include "UserSystem.h"

UserSystem::UserSystem(const UserValidationService& userValidationService) : userValidationService(userValidationService) {}

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
    std::vector<std::string> errors = userValidationService.validate(user);
    if (!errors.empty()) {
        throw ValidationFailedException("User validation failed!", errors);
    }
    users.push_back(user);
}

std::shared_ptr<User> UserSystem::findUser(const std::string& username) const {
    for (auto user : users) {
        if (user->getUsername() == username) {
            return user;
        }
    }
    throw std::invalid_argument("Username not found.\n");
    return nullptr;
}

void UserSystem::loadUserSystem(std::fstream& file, const BookSystem& bookSystem) {
    std::string usersCount;
    file >> usersCount;
    for (size_t i = 0; i < static_cast<size_t>(std::stoull(usersCount)); i++) {
        std::string userType, username, password;
        file >> userType >> username >> password;
        try {
            std::shared_ptr<User> user = UserFactory::createUser(userType, username, password);
            user->loadUser(file, bookSystem);
            addUser(user);
        }
        catch (const std::invalid_argument& ex) {
            std::cout << ex.what() << "\n" << std::endl;
        }
    }
}

void UserSystem::saveUserSystem(std::fstream& file) const {
    file << std::to_string(users.size()) << '\n';
    for (auto user : users) {
        user->saveUser(file);
    }
}