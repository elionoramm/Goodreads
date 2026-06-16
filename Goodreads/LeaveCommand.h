#pragma once
#include "Command.h"
#include "GoodReads.h"

class Leave : public Command {
private:
	GoodReads& goodReads;
public:
	Leave(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};