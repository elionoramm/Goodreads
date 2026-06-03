#include "UsernameValidator.h"

UsernameValidator::UsernameValidator(
    std::optional<size_t> minLength,
    std::optional<size_t> maxLength,
    bool lowercaseLetterRequired,
    bool uppercaseLetterRequired,
    bool specialCharactersAllowed
) : StringPropertyValidator(minLength, maxLength, lowercaseLetterRequired, uppercaseLetterRequired),
specialCharactersAllowed(specialCharactersAllowed) {
}

std::unique_ptr<UserValidator> UsernameValidator::clone() const {
    return std::make_unique<UsernameValidator>(*this);
}

std::vector<std::string> UsernameValidator::validate(const std::shared_ptr<User>& user) const {
    std::vector<std::string> errors;
    validateCommonStringRules(user->getUsername(), "username", errors);

    if (!specialCharactersAllowed) {
        bool valid = std::ranges::none_of(user->getUsername(), [](char symbol) {
                return !(isalnum(symbol) || symbol == '_');
            }
        );
        if (!valid) {
            errors.emplace_back("Username must contain only letters, digits or underscore.");
        }
    }
    return errors;
}

UsernameValidator::Builder& UsernameValidator::Builder::allowSpecialCharacters(bool value) {
    specialCharactersAllowed = value;
    return *this;
}

UsernameValidator UsernameValidator::Builder::build() const {
    return UsernameValidator(
        minLengthValue,
        maxLengthValue,
        lowercaseLetterRequiredValue,
        uppercaseLetterRequiredValue,
        specialCharactersAllowed
    );
}