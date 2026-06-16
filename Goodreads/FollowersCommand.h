#pragma once
#include "Command.h"
#include "GoodReads.h"

class Followers : public Command {
private:
	GoodReads& goodReads;
public:
	Followers(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};