#pragma once
#include "Command.h"
#include "GoodReads.h"

class Exit : public Command {
private:
	GoodReads& goodReads;
public:
	Exit(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};