#pragma once
#include "Command.h"
#include "GoodReads.h"

class Login : public Command {
private:
	GoodReads& goodReads;
public:
	Login(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};