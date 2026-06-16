#pragma once
#include "Command.h"
#include "GoodReads.h"

class AcceptOffer : public Command {
private:
	GoodReads& goodReads;
public:
	AcceptOffer(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};