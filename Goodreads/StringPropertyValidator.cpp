#include "StringPropertyValidator.h"
#include <format>

StringPropertyValidator::StringPropertyValidator(
    std::optional<size_t> minLength,
    std::optional<size_t> maxLength,
    bool lowercaseLetterRequired,
    bool uppercaseLetterRequired
) :  minLength(minLength), maxLength(maxLength),lowercaseLetterRequired(lowercaseLetterRequired),
uppercaseLetterRequired(uppercaseLetterRequired){}

void StringPropertyValidator::validateCommonStringRules(const std::string& value, const std::string& field, std::vector<std::string>& errors) const {
    if (minLength.has_value() && value.length() < minLength.value()) {
        errors.push_back(std::format("{} is too short. Expected at least {} symbols.", field, minLength.value()));
    }

    if (maxLength.has_value() && value.length() > maxLength.value()) {
        errors.push_back(std::format("{} is too long. Expected no more than {} symbols.", field, maxLength.value()));
    }

    if (lowercaseLetterRequired && std::ranges::none_of(value, [](unsigned char c) { return std::islower(c); })) {
        errors.push_back(std::format("{} must contain at least one lowercase letter.", field));
    }

    if (uppercaseLetterRequired && std::ranges::none_of(value, [](unsigned char c) { return std::isupper(c); })) {
        errors.push_back(std::format("{} must contain at least one uppercase letter.", field));
    }
}