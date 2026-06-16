#pragma once
#include "Command.h"
#include "GoodReads.h"

class AddSynopsis : public Command {
private:
	GoodReads& goodReads;
public:
	AddSynopsis(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};