#include "ReadMSGCommand.h"

ReadMSG::ReadMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void ReadMSG::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: read-msg <index>\n");
	}
	try {
		int index = std::stoi(params[0]);
		activeUser->readMessage(index);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid index.\n" << std::endl;
	}
}