#pragma once
#include <optional>
#ifndef STRING_PROPERTY_VALIDATOR_BUILDER_BASE_HPP
#define STRING_PROPERTY_VALIDATOR_BUILDER_BASE_HPP


template <class DerivedBuilder>
class StringPropertyValidatorBuilderBase {
private:
    DerivedBuilder& self() {
        return static_cast<DerivedBuilder&>(*this);
    }
protected:
    std::optional<size_t> minLengthValue;
    std::optional<size_t> maxLengthValue;
    bool lowercaseLetterRequiredValue = false;
    bool uppercaseLetterRequiredValue = false;

public:

    DerivedBuilder& minLength(size_t value) {
        minLengthValue = value;
        return self();
    }

    DerivedBuilder& maxLength(size_t value) {
        maxLengthValue = value;
        return self();
    }

    DerivedBuilder& requireLowercaseLetter(bool value = true) {
        lowercaseLetterRequiredValue = value;
        return self();
    }

    DerivedBuilder& requireUppercaseLetter(bool value = true) {
        uppercaseLetterRequiredValue = value;
        return self();
    }
};
#endif // STRING_PROPERTY_VALIDATOR_BUILDER_BASE_HPP