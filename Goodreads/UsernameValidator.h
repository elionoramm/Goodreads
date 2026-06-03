#pragma once
#include "StringPropertyValidator.h"
#include "StringPropertyValidatorBuilderBase.hpp"
#include "UserValidator.h"

class UsernameValidator : public StringPropertyValidator {
private:
    bool specialCharactersAllowed;
    UsernameValidator(std::optional<size_t> minLength, std::optional<size_t> maxLength, bool lowercaseLetterRequired, bool uppercaseLetterRequired, bool specialCharactersAllowed);
public:
    std::vector<std::string> validate(const std::shared_ptr<User>& user) const override;
    std::unique_ptr<UserValidator> clone() const override;

    class Builder : public StringPropertyValidatorBuilderBase<UsernameValidator::Builder> {
    private:
        bool specialCharactersAllowed = true;
    public:
        Builder& allowSpecialCharacters(bool value = true);
        UsernameValidator build() const;
    };
};