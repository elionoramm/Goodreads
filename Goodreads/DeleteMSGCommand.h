#pragma once
#include "Command.h"
#include "GoodReads.h"

class DeleteMSG : public Command {
private:
	GoodReads& goodReads;
public:
	DeleteMSG(GoodReads& goodReads);
	void execute(std::vector<std::string> substrings) override;
};