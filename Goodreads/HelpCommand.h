#pragma once
#include "Command.h"
#include "GoodReads.h"

class Help : public Command {
private:
	GoodReads& goodReads;
public:
	Help(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};