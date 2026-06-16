#include "HelpCommand.h"

Help::Help(GoodReads& goodReads) : goodReads(goodReads) {}

void Help::execute(std::vector<std::string> params) {
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 0) {
		throw WrongCommandUsage("Usage: help\n");
	}
	goodReads.getActiveUser()->help();
}
