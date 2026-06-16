#pragma once
#include "Command.h"
#include "GoodReads.h"

class ShowShelf : public Command {
private:
	GoodReads& goodReads;
public:
	ShowShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};