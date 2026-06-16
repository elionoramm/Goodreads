#pragma once
#include <stdexcept>
#include <vector>

class UserAlreadyExistsException : public std::runtime_error {
public:
    explicit UserAlreadyExistsException(const std::string& message);
    using std::runtime_error::what;
};

class ValidationFailedException : public std::runtime_error {
private:
    std::vector<std::string> validationErrors;
public:
    ValidationFailedException(const std::string& message, const std::vector<std::string>& validationErrors);
    using std::runtime_error::what;
    const std::vector<std::string>& getValidationErrors() const;
};

class NotLoggedIn : public std::runtime_error {
public:
    explicit NotLoggedIn();
    using std::runtime_error::what;
};

class WrongCommandUsage : public std::runtime_error {
public:
    explicit WrongCommandUsage(const std::string& message);
    using std::runtime_error::what;
};

class WrongUserCommand : public std::runtime_error {
public:
    explicit WrongUserCommand(const std::string& userType);
    using std::runtime_error::what;
};