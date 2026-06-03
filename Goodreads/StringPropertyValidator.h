#pragma once
#include <memory>
#include <string>
#include <vector>
#include <optional>
#include "UserValidator.h"

class StringPropertyValidator : public UserValidator {
private:
    std::optional<size_t> minLength;
    std::optional<size_t> maxLength;
    bool lowercaseLetterRequired;
    bool uppercaseLetterRequired;
protected:
    StringPropertyValidator(std::optional<size_t> minLength, std::optional<size_t> maxLength, bool lowercaseLetterRequired, bool uppercaseLetterRequired);
    void validateCommonStringRules (const std::string& value, const std::string& field, std::vector<std::string>& errors) const;
};