#pragma once
#include "Command.h"
#include "GoodReads.h"

class AddToShelf : public Command {
private:
	GoodReads& goodReads;
public:
	AddToShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};