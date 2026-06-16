#include "DeleteMSGCommand.h"

DeleteMSG::DeleteMSG(GoodReads& goodReads) : goodReads(goodReads) {}

void DeleteMSG::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 1) {
		throw WrongCommandUsage("Usage: delete-msg <index>\n");
	}
	try {
		int index = std::stoi(params[0]);
		activeUser->deleteMessage(index);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid index.\n" << std::endl;
	}
}
