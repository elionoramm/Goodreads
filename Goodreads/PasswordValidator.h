#pragma once
#include "UserValidator.h"
#include "StringPropertyValidator.h"
#include "StringPropertyValidatorBuilderBase.hpp"

class PasswordValidator : public StringPropertyValidator {
private:
    bool specialCharacterRequired;
    PasswordValidator(std::optional<size_t> minLength, std::optional<size_t> maxLength, bool lowercaseLetterRequired, bool uppercaseLetterRequired, bool specialCharacterRequired);
public:
    std::vector<std::string> validate(const std::shared_ptr<User>& user) const override;
    std::unique_ptr<UserValidator> clone() const override;

    class Builder : public StringPropertyValidatorBuilderBase<PasswordValidator::Builder> {
    private:
        bool specialCharacterRequiredValue = true;
    public:
        Builder& requireSpecialCharacter(bool value = true);
        PasswordValidator build() const;
    };
};