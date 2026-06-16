#pragma once
#include "Command.h"
#include "GoodReads.h"

class AddBirthday : public Command {
private:
	GoodReads& goodReads;
public:
	AddBirthday(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};