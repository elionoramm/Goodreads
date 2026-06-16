#pragma once
#include "Command.h"
#include "GoodReads.h"

class Logout : public Command {
private:
	GoodReads& goodReads;
public:
	Logout(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};