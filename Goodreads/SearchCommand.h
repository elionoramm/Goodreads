#pragma once
#include "Command.h"
#include "GoodReads.h"

class Search : public Command {
private:
	GoodReads& goodReads;
public:
	Search(GoodReads& goodReads);
	bool fuzzySearch(const std::string& str1, const std::string& str2) const;
	void execute(std::vector<std::string> substrings) override;
};