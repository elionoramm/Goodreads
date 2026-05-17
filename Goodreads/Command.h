#pragma once
#include <string>
#include <vector>
class Command {
public:
	virtual void execute(std::vector<std::string> substrings) = 0;
};