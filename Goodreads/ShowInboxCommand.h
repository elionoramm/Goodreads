#pragma once
#include "Command.h"
#include "GoodReads.h"

class ShowInbox : public Command {
private:
	GoodReads& goodReads;
public:
	ShowInbox(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};