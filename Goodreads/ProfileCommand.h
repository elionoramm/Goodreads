#pragma once
#include "Command.h"
#include "GoodReads.h"

class Profile : public Command {
private:
	GoodReads& goodReads;
public:
	Profile(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};