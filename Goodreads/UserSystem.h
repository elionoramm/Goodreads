#pragma once
#include <vector>
#include <memory>
#include <string>
#include <optional>
#include <format>
#include <fstream>
#include "User.h"
#include "UserFactory.h"
#include "UserValidationService.h"
#include "BookSystem.h"
#include "CustomUserExceptions.h"

class UserSystem {
private:
    UserFactory userFactory;
    std::vector<std::shared_ptr<User>> users;
    UserValidationService userValidationService;
public:
	UserSystem() = default;
    UserSystem(const UserValidationService& userValidationService);
    const std::vector<std::shared_ptr<User>>& getUsers() const;
    UserFactory& getUserFactory();
    std::optional<std::shared_ptr<User>> operator[](const std::string& username) const;
    void addUser(const std::shared_ptr<User>& user);
    std::shared_ptr<User> findUser(const std::string& username) const;
    void loadUserSystem(std::fstream& file, const BookSystem& bookSystem);
    void saveUserSystem(std::fstream& file) const;
};