#pragma once
#include "Command.h"
#include "GoodReads.h"

class RemoveFromShelf : public Command {
private:
	GoodReads& goodReads;
public:
	RemoveFromShelf(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};