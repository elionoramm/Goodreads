#pragma once
#include "Command.h"
#include "GoodReads.h"

class Offer : public Command {
private:
	GoodReads& goodReads;
public:
	Offer(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};