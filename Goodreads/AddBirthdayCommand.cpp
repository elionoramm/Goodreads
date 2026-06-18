#include "AddBirthdayCommand.h"

AddBirthday::AddBirthday(GoodReads& goodReads) : goodReads(goodReads) {}

void AddBirthday::execute(std::vector<std::string> params) {
	std::shared_ptr<Reader> activeUser = goodReads.getActiveReader();
	if (goodReads.getActiveUser() == nullptr) {
		throw NotLoggedIn();
	}
	if (params.size() != 0 && params.size() != 1) {
		throw WrongCommandUsage("Usage: add-birthday <date>*\n");
	}
	Date birthday;
	if (params.size() == 0) {
		birthday = Date();
	}
	else if (params.size() == 1) {
		try {
			birthday = Date(params[0]);
		}
		catch (const std::out_of_range& e) {
			std::cout << e.what() << std::endl;
			return;
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
			return;
		}
	}
	activeUser->setBirthday(birthday);
}