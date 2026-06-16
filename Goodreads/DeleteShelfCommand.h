#pragma once
#include "Command.h"
#include "GoodReads.h"

class DeleteShelf : public Command {
private:
	GoodReads& goodReads;
public:
	DeleteShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};