#include "CustomUserExceptions.h"
UserAlreadyExistsException::UserAlreadyExistsException(const std::string& message) : std::runtime_error(message) {}

ValidationFailedException::ValidationFailedException(const std::string& message, const std::vector<std::string>& validationErrors)
    : std::runtime_error(message), validationErrors(validationErrors) {
}

const std::vector<std::string>& ValidationFailedException::getValidationErrors() const {
    return validationErrors;
}

NotLoggedIn::NotLoggedIn() : std::runtime_error(message) {}

WrongCommandUsage::WrongCommandUsage(const std::string& message) : std::runtime_error(message) {}

WrongUserCommand::WrongUserCommand(const std::string& userType, const std::string& command) : userType(userType), 
    command(command), std::runtime_error(message) {}