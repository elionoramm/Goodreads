#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include "User.h"

class UserValidator {
public:
    virtual ~UserValidator() = default;
    virtual std::vector<std::string> validate(const std::shared_ptr<User>& user) const = 0;
    virtual std::unique_ptr<UserValidator> clone() const = 0;
};