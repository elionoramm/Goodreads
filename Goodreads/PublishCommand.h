#pragma once
#include "Command.h"
#include "GoodReads.h"

class Publish : public Command {
private:
	GoodReads& goodReads;
public:
	Publish(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};