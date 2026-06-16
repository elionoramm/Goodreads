#pragma once
#include "Command.h"
#include "GoodReads.h"

class Register : public Command {
private:
	GoodReads& goodReads;
public:
	Register(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};