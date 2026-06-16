#pragma once
#include "Command.h"
#include "GoodReads.h"

class CreateShelf : public Command {
private:
	GoodReads& goodReads;
public:
	CreateShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};