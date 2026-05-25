#include <iostream>
#include "Date.h"
Date::Date() : day(0), month(0), year(0) {}

Date::Date(const std::string& string) {
	std::string number;
	std::vector<int> substrings;
	for (int i = 0; i <= string.size(); i++) {
		if (string[i] != '/' && string[i] != '\0') {
			number = number + string[i];
		}
		else {
			substrings.push_back(std::stoi(number));
			number = "";
		}
	}
	try{
		if (substrings.size() != 3) {
			throw std::invalid_argument("Invalid date format. Expected format: 'day/month/year'.");
		}
		if (substrings[2] < 0) {
			throw std::out_of_range("Year cannot be negative.");
		}
		if (substrings[1] < 1 || substrings[1] > 12) {
			throw std::out_of_range("Month must be between 1 and 12.");
		}
		if (substrings[1] == 1 || substrings[1] == 3 || substrings[1] == 5 || substrings[1] == 7 || substrings[1] == 8 || substrings[1] == 10 || substrings[1] == 12) {
			if (substrings[0] < 1 || substrings[0] > 31) {
				throw std::out_of_range("Day must be between 1 and 31.");
			}
		}
		else if (substrings[1] == 4 || substrings[1] == 6 || substrings[1] == 9 || substrings[1] == 11) {
			if (substrings[0] < 1 || substrings[0] > 30) {
				throw std::out_of_range("Day must be between 1 and 30.");
			}
		}
		else if (substrings[1] == 2 && substrings[2] % 4 == 0 && substrings[2] % 100 != 0 && substrings[2] % 400 == 0) {
			if (substrings[0] < 1 || substrings[0] > 29) {
				throw std::out_of_range("Day must be between 1 and 29.");
			}
		}
		else if (substrings[1] == 2) {
			if (substrings[0] < 1 || substrings[0] > 28) {
				throw std::out_of_range("Day must be between 1 and 28.");
			}
		}
	}
	catch (const std::out_of_range& exception) {
		std::cerr << "Invalid date: " << exception.what() << std::endl;
		throw;
	}
	catch (const std::invalid_argument& exception) {
		std::cerr << "Invalid date: " << exception.what() << std::endl;
		throw;
	}
	this->day = substrings[0];
	this->month = substrings[1];
	this->year = substrings[2];
}

void Date::printDate() const {
	if (day == 0 && month == 0 && year == 0) {
		std::cout << "N/A" << std::endl;
		return;
	}
	std::cout << (day < 10 ? "0" : "") << day << "/" << (month < 10 ? "0" : "") << month << "/" << year << std::endl;
}

bool Date::isSet() const {
	if (day == 0 || month == 0 || year == 0) {
		return false;
	}
	return true;
}