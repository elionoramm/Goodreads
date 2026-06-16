#pragma once
#include "Command.h"
#include "GoodReads.h"

class ReadMSG : public Command {
private:
	GoodReads& goodReads;
public:
	ReadMSG(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};