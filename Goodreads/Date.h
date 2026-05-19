#pragma once
#include <string>
#include <vector>
class Date {
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date();
	Date(const std::string& string);
	void printDate() const;
};