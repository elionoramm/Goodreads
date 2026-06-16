#pragma once
#include "Command.h"
#include "GoodReads.h"

class DeleteBook : public Command {
private:
	GoodReads& goodReads;
public:
	DeleteBook(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};