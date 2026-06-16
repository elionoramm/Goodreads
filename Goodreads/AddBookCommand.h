#pragma once
#include "Command.h"
#include "GoodReads.h"

class AddBook : public Command {
private:
	GoodReads& goodReads;
public:
	AddBook(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};