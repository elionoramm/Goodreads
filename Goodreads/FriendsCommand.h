#pragma once
#include "Command.h"
#include "GoodReads.h"

class Friends : public Command {
private:
	GoodReads& goodReads;
public:
	Friends(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};