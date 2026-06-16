#pragma once
#include "Command.h"
#include "GoodReads.h"

class Follow : public Command {
private:
	GoodReads& goodReads;
public:
	Follow(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};